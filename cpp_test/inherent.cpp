#include <iostream>
#include <functional>

class base {
public:
    base(int &x) : x(x) { }
    void print_x() { std::cout << x.get() << std::endl; }

private:
    std::reference_wrapper<int> x;
};

class derived : public base {
public:
    derived() : base(y) { }
private:
    int y = 42;
};

int main() {
    derived d;
    d.print_x();
}
