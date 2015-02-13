
#include <iostream>

int x;

int f()
{
    x += 10;
    return 1;
}

int x_f()
{
    return x;
}

int& X()
{
    return x;
}

int add(int a, int b)
{
    return a + b;
}

int main (int argc, char* argv[])
{
	x = 0;
	x += f();
	std::cout << "(1=) x: " << x << std::endl;

	x = 0;
	x = x + f();
	std::cout << "(2=) x: " << x << std::endl;

	x = 0;
	x = f() + x;
	std::cout << "(3?) x: " << x << std::endl;

	std::cout << "function returns x: " << std::endl;

	x = 0;
	x = x_f() + f();
	std::cout << "(4=) x: " << x << std::endl;

	x = 0;
	x = f() + x_f();
	std::cout << "(5!) x: " << x << std::endl;

	std::cout << "with referece: " << std::endl;

	x = 0;
	X() += f();
	std::cout << "(6=) x: " << x << std::endl;

	x = 0;
	X() = X() + f();
	std::cout << "(7=) x: " << x << std::endl;

	x = 0;
	X() = f() + X();
	std::cout << "(8!) x: " << x << std::endl;

	std::cout << "add function: " << std::endl;

	x = 0;
	x = add(x, f());
	std::cout << "(9=) x: " << x << std::endl;

	x = 0;
	x = add(f(), x);
	std::cout << "(10!) x: " << x << std::endl;

	x = 0;
	x = add(X(), f());
	std::cout << "(11=) x: " << x << std::endl;

	x = 0;
	x = add(f(), X());
	std::cout << "(12!) x: " << x << std::endl;
}
