/* This is a test of interthread communication between two choices:
 *	1) pipe with epoll listener
 *	2) mutex with direct access
 */

#include "pipe_vs_mutex.h"

/***** neeeded for classes in header file ******/
template<>
void auto_epoll_handle<fd_counter>::operator() () { };

__thread uint64_t fd_counter::inc_handle_t::batcher;

/***** run time settings ******/

constexpr int long_run = 20000000;
constexpr int short_run = 2000000;
constexpr int realistic_run = 1000000;

const int run_time = realistic_run;

/***** no sync *****/

volatile int value = 0;

int loop_none(bool inc, int limit)
{
    std::cout << "Started " + std::to_string(inc) + " " + std::to_string(limit) + "\n";

    for (int i = 0; i < limit; ++i) {
	if (inc) {
	    ++value;
	} else {
	    --value;
	}
    }

    return 0;
}

int run_none()
{
    auto func = std::bind(loop_none, true, run_time);

    auto t1 = std::thread(func);
    auto t2 = std::thread(func);
    auto t3 = std::thread(func);
    auto t4 = std::thread(func);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << value << std::endl;
}

/***** for atomics *****/

std::atomic<int> value_atomic(0);

int loop_atomic(bool inc, int limit)
{
    std::cout << "Started " + std::to_string(inc) + " " + std::to_string(limit) + "\n";

    for (int i = 0; i < limit; ++i) {
	if (inc) {
	    ++value_atomic;
	} else {
	    --value_atomic;
	}
    }

    return 0;
}

int run_atomic()
{
    auto func = std::bind(loop_atomic, true, run_time);

    auto t1 = std::thread(func);
    auto t2 = std::thread(func);
    auto t3 = std::thread(func);
    auto t4 = std::thread(func);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << value_atomic << std::endl;
}

/***** for mutex *****/

volatile int value_mutex = 0;
std::mutex mutex;

int loop_mutex(bool inc, int limit)
{
    std::cout << "Started " + std::to_string(inc) + " " + std::to_string(limit) + "\n";

    for (int i = 0; i < limit; ++i) {
	std::lock_guard<std::mutex> guard(mutex);
	if (inc) {
	    ++value_mutex;
	} else {
	    --value_mutex;
	}
    }

    return 0;
}

int run_mutex()
{
    auto func = std::bind(loop_mutex, true, run_time);

    auto t1 = std::thread(func);
    auto t2 = std::thread(func);
    auto t3 = std::thread(func);
    auto t4 = std::thread(func);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << value_mutex << std::endl;
}

/***** for eventfd *****/

int loop_pipe(fd_counter& counter, bool inc, int limit)
{
    std::cout << "Started " + std::to_string(inc) + " " + std::to_string(limit) + "\n";

    for (int i = 0; i < limit; ++i) {
	if (inc) {
	    counter.inc();
	} else {
	    counter.inc();
	    std::cerr << "no decrementing yet";
	    exit(EXIT_FAILURE);
	}
    }

    return 0;
}

int run_pipe()
{
    fd_counter counter(0);

    auto func = std::bind(loop_pipe, std::ref(counter), true, run_time);

    auto t1 = std::thread(func);
    auto t2 = std::thread(func);
    auto t3 = std::thread(func);
    auto t4 = std::thread(func);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << counter.get() << std::endl;

    exit(EXIT_SUCCESS);
}

/***** for spinlock *****/

volatile int value_spinlock = 0;
dss::spinlock spinlock;

int loop_spinlock(bool inc, int limit)
{
    std::cout << "Started " + std::to_string(inc) + " " + std::to_string(limit) + "\n";

    for (int i = 0; i < limit; ++i) {
	std::lock_guard<dss::spinlock> guard(spinlock);
	if (inc) {
	    ++value_spinlock;
	} else {
	    --value_spinlock;
	}
    }

    return 0;
}

int run_spinlock()
{
    auto func = std::bind(loop_spinlock, true, run_time);

    auto t1 = std::thread(func);
    auto t2 = std::thread(func);
    auto t3 = std::thread(func);
    auto t4 = std::thread(func);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << value_spinlock << std::endl;
}

/***** main *****/

int main(int argc, char* argv[])
{
    if (argc == 1) {
	std::cerr << "please give a test to run" << std::endl;
	exit(EXIT_FAILURE);
    }

    std::string test = argv[1];

    if (test == "none") {
	run_none();
    } else if (test == "mutex") {
	run_mutex();
    } else if (test == "atomic") {
	run_atomic();
    } else if (test == "pipe") {
	run_pipe();
    } else if (test == "spin") {
	run_spinlock();
    } else {
	std::cerr << "test: " << test << " not found\n";
    }
}
