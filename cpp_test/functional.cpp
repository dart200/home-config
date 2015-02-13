
#include <stack>
#include <assert.h>
#include <iostream>
#include <functional>
#include <boost/context/all.hpp>

#include <unistd.h>
#include <sys/user.h>

typedef bool _Bool;
#define __KERNEL__
#include <linux/bcache-net.h>
#undef __KERNEL__

namespace ctx = boost::context;

#define COROUTINE_STACK_SIZE      (PAGE_SIZE * 4)

typedef std::function<void(void)> coroutine_fn;

struct context_stat
{
    ctx::fcontext_t* context;
    char* stack_alloc; // will be 0 for main "context"

    context_stat(ctx::fcontext_t* _context, char* _stack_alloc)
	: context(_context), stack_alloc(_stack_alloc) {  };
};

static std::stack<context_stat> context_stack;

static void coroutine_start(intptr_t arg)
{
    coroutine_fn* fn = (coroutine_fn*) arg;
    (*fn)();

    context_stat cur_stat = context_stack.top();
    context_stack.pop();

    ctx::jump_fcontext(cur_stat.context, context_stack.top().context,
		       (intptr_t) cur_stat.stack_alloc);
}

void run_as_coroutine(coroutine_fn* fn)
{
    char* stack_alloc = ((char*)aligned_alloc(PAGE_SIZE, COROUTINE_STACK_SIZE));

    /* stack pointer has to point to the end of the allocated space,
     * because the stack grows from high to low. */
    void *sp = stack_alloc + COROUTINE_STACK_SIZE;
    ctx::fcontext_t* new_context = ctx::make_fcontext(sp, COROUTINE_STACK_SIZE,
						      coroutine_start);

    assert(!context_stack.empty());
    ctx::fcontext_t* cur = context_stack.top().context;

    // save next context on stack (so we don't have to pass it in)
    context_stack.emplace(new_context, stack_alloc);

    intptr_t ret = ctx::jump_fcontext(cur, new_context,
				      (intptr_t) fn);

    // if another coroutine jumped to this point passing a
    //	value for ret, the routine was finisehd it passed the
    //	stack allocation to be freed
    if (ret) {
	free((char*)ret);
    }
}

void my_func2(int x, int y)
{
    std::cout << "I suppose multiplication is a bit more interesting:\n"
	      << x << " * " << y << " = " << (x * y) << "."
	      << std::endl;
    std::cout << "context_stack_size in my_func2: " << context_stack.size()
	      << std::endl;
}

void my_func(int x)
{
    std::cout << "why print something as boring as: " << x << "?"
	      << std::endl;

    coroutine_fn my_func2_fn = std::bind(my_func2, 42, 10);
    run_as_coroutine(&my_func2_fn);

}

int main()
{
    ctx::fcontext_t main;
    context_stack.emplace(&main, (char*)0);

    coroutine_fn my_func_fn = std::bind(my_func, 42);
    run_as_coroutine(&my_func_fn);

    std::cout << "context_stack_size at end: " << context_stack.size()
	      << std::endl;

    return 0;
}

static __attribute__((constructor)) void init_main_ctx()
{
}
