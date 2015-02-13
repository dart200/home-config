
#include <iostream>

template<typename T>
class const_ref
{
public:
    const_ref(const T& ref_var) : ref_var(ref_var) { };

    void print() { std::cout << ref_var << std::endl; }

private:
    const T& ref_var;
};

template<typename T>
const const_ref<T> make_cref(const T& ref_var)
{
    return const_ref<T>(ref_var);
};

void print(int x)
{
    std::cout << x << std::endl;
};

int main()
{
    int x = 5;
    auto cref = make_cref(x);

    print(x);
    cref.print();

    x = 42;
    print(x);
    cref.print();
};
