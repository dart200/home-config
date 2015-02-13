
#include <iostream>
#include <functional>

struct base
{
    int blah;
};

struct foo : public base
{
    int nope;
};

using init_list = std::initializer_list<std::reference_wrapper<base>>;

void func (init_list struct_list)
{
    for (base& b : struct_list) {
	std::cout << b.blah;
    }

    std::cout << std::endl;
}

int main()
{
    base b { .blah = 4 };
    foo f;
    f.blah = 2;
    f.nope = 666;

    func({b, f});
}
