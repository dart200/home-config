
#include <iostream>
#include <unistd.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <boost/context/all.hpp>

#define COROUTINE_STACK_SIZE      (PAGE_SIZE * 4)

namespace ctx = boost::context;

ctx::fcontext_t ctx_main;

ctx::fcontext_t* ctx_foo;
ctx::fcontext_t* ctx_bar;

void* ctx_alloc(ctx::fcontext_t*& new_fcontext, void(*fn)(intptr_t) )
{
    char* stack_alloc = ((char*)aligned_alloc(PAGE_SIZE,
				PAGE_SIZE + COROUTINE_STACK_SIZE + PAGE_SIZE));
    mprotect(stack_alloc, 1, PROT_READ);
    mprotect(stack_alloc + PAGE_SIZE + COROUTINE_STACK_SIZE,
	     1, PROT_READ);

    /*
     * stack pointer has to point to the end of the allocated space,
     * because the stack grows from high to low.
     */
    void *sp = stack_alloc + PAGE_SIZE + COROUTINE_STACK_SIZE;
    new_fcontext = ctx::make_fcontext(sp, COROUTINE_STACK_SIZE, fn);

    return stack_alloc;
}

#define PRINT_VAR(name) std::cout << var_ ## name << std::endl;

int var_foo = 0;
int var_bar = 0;

void foo(intptr_t arg)
{
    var_foo++;
    int x = (int) ctx::jump_fcontext(ctx_foo, ctx_bar, 5);
    var_foo += x;
    ctx::jump_fcontext(ctx_foo, &ctx_main, 5);
}

void bar(intptr_t arg)
{
    var_bar += (int) arg;
    //ctx::jump_fcontext(ctx_bar, &ctx_main, 5);
    ctx::jump_fcontext(ctx_bar, ctx_foo, 5);
}

int main()
{
    void* alloc_foo = ctx_alloc(ctx_foo, foo);
    void* alloc_bar = ctx_alloc(ctx_bar, bar);

    int y = (int) ctx::jump_fcontext(&ctx_main, ctx_foo, 0);
    PRINT_VAR(foo);
    PRINT_VAR(bar);

    std::cout << "y:" << y << std::endl;

    free(alloc_bar);
    free(alloc_foo);
}
