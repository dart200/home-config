#include <functional>
#include <iostream>

typedef std::function<int(void)> my_closure_fn;

/*
 * generates a function that contains a counter initilized to a given
 * value which returns and then increments the counter each call.
 */
my_closure_fn inc_func_gen(int init_val)
{
    auto closure = [=] () mutable -> int {
	return init_val++;
    };

    return closure;
}

my_closure_fn layered_func_gen(int init_val)
{
    auto closure = inc_func_gen(init_val - 1);
    closure();
    return closure;
}

int main()
{
    std::cout << "closure 1:" << std::endl;
    my_closure_fn c1 = layered_func_gen(1);
    std::cout << "1: " << c1() << std::endl;
    std::cout << "2: " << c1() << std::endl;
    std::cout << "3: " << c1() << std::endl;

    std::cout << "closure 2:" << std::endl;
    my_closure_fn c2 = layered_func_gen(5);
    std::cout << "5: " << c2() << std::endl;
    std::cout << "6: " << c2() << std::endl;
    std::cout << "7: " << c2() << std::endl;

    std::cout << "closure 3:" << std::endl;
    my_closure_fn c3 = layered_func_gen(-40);
    std::cout << "-40: " << c3() << std::endl;
    std::cout << "-39: " << c3() << std::endl;
    std::cout << "-38: " << c3() << std::endl;

    std::cout << "mix:" << std::endl;
    std::cout << "(1) 4: " << c1() << std::endl;
    std::cout << "(2) 8: " << c2() << std::endl;
    std::cout << "(3) -37: " << c3() << std::endl << std::endl;

    my_closure_fn c1_copy_val(c1);
    my_closure_fn c2_copy_val(c2);
    my_closure_fn c3_copy_val(c3);

    my_closure_fn c1_copy_ref(std::ref(c1));
    my_closure_fn c2_copy_ref(std::ref(c2));
    my_closure_fn c3_copy_ref(std::ref(c3));

    std::cout << "mix (copy by value):" << std::endl;
    std::cout << "(1) 5: " << c1_copy_val() << std::endl;
    std::cout << "(2) 9: " << c2_copy_val() << std::endl;
    std::cout << "(3) -36: " << c3_copy_val() << std::endl;

    std::cout << "mix (original):" << std::endl;
    std::cout << "(1) 5: " << c1() << std::endl;
    std::cout << "(2) 9: " << c2() << std::endl;
    std::cout << "(3) -36: " << c3() << std::endl << std::endl;

    std::cout << "mix (copy by reference):" << std::endl;
    std::cout << "(1) 6: " << c1_copy_ref() << std::endl;
    std::cout << "(2) 10: " << c2_copy_ref() << std::endl;
    std::cout << "(3) -35: " << c3_copy_ref() << std::endl;

    std::cout << "mix (original):" << std::endl;
    std::cout << "(1) 7: " << c1() << std::endl;
    std::cout << "(2) 11: " << c2() << std::endl;
    std::cout << "(3) -34: " << c3() << std::endl;

    return 0;
}
