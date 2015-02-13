#include <iostream>

int main (int argc, char** argv)
{
    union {
	int x;
	int y;
    };

    x = 1;
    y = 2;

    std::cout << " x + y = " << (x+y) << std::endl;

    return 0;
}
