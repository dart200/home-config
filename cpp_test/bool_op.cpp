#include <iostream>
#include <array>

int func(int x) {
    std::cout << x << std::endl;
}

class foo {
public:
    foo() = default;
    std::array<int, 10> val;
};

int main() {
    foo bar {};
    std::cout << bar.val[0] << std::endl;
}
