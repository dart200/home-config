#include <sys/eventfd.h>

#include <thread>
#include <future>
#include <iostream>
#include <mutex>
#include <atomic>
#include <chrono>

#include <Datera/dfs_epoll.h>
#include <Datera/dss_util.h>

class fd_counter
{
    class inc_handle_t : public auto_epoll_handle<fd_counter> {
    public:
	inc_handle_t(fd_counter& c, int watch_fd)
	    : auto_epoll_handle<fd_counter>(c, watch_fd) { };

	virtual void operator()() {
	    uint64_t nr_primes = 0;
	    if (read(fd, &nr_primes, 8) != 8)
		LOG(FATAL) << "read() fail in pool_event_handle()";

	    c.value += nr_primes;
	};

	static  __thread uint64_t batcher;
	void prime() {
	    ++batcher;

	    if (batcher == 10) {
		write(fd, &batcher, 8);
		batcher = 0;
	    }
	};
    };

public:
    fd_counter(int init)
	: value(init),
	  internal_thread(std::bind(&fd_counter::run, this)) { };
    fd_counter() : fd_counter(0) { };

    int inc() {
	if (!inc_handle)
	    std::cerr << "handle not inited";
	inc_handle->prime();
    };

    int get() { return value; };

private:
    volatile int    value;
    inc_handle_t*   inc_handle = new inc_handle_t(*this, eventfd(0, EFD_NONBLOCK));

    std::thread	    internal_thread;
    epoll_manager*  epoll;

    void run() {
	epoll = new epoll_manager();
	epoll->watch(inc_handle);
	epoll->loop();
    };
};

namespace dss
{
    class spinlock;
};

class dss::spinlock
{
public:
    void lock() {
	while (flag.test_and_set(std::memory_order_acquire))
	    ; // spin
    }

    void unlock() {
	flag.clear(std::memory_order_release);
    }
private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

// vim: ft=cpp
