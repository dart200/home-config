
#include <iostream>
#include <functional>

typedef std::function<void(void)> func;
struct func_container {
    func f;
};

void run_container(func_container*  c)
{
    c->f();
}

void run_func(func f)
{
    func_container c;
    c.f = f;

    run_container(&c);
}

int y = 0;

void inc(int x)
{
    y++;
}

int main (int argc, char* argv[])
{
    func f = std::bind(inc, 1);
    run_func(f);
    std::cout << "y: " << y;
}
