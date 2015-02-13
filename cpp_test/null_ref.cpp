
#include <iostream>
#include <string>

void print_int(const int& x) {
    std::cout << x << std::endl;
}

int main() {
    int x = 420;
    int* xPtr = &x;
    xPtr = nullptr;

    print_int(*xPtr);

    std::cout << "done" << std::endl;
}
