
#include <iostream>

template<typename T>
class const_ref
{
public:
    const_ref(const T& ref_var) : ref_var(ref_var) {
	std::cout << "normal ctr called:\t"<< this << std::endl;
    };

#if 0 // NOT A VALID CTR
    const_ref(const const_ref<T> what)
	: ref_var(what.ref_var) {
	std::cout << "not sure ctr called" << std::endl;
    };
#endif

    const_ref(const const_ref<T>& copy)
	: ref_var(copy.ref_var) {
	std::cout << "copy ctr called:\t" << this << std::endl;
    };

    const_ref(const const_ref<T>&& move)
	: ref_var(move.ref_var) {
	std::cout << "move ctr called:\t" << this << std::endl;
    };
    ~const_ref() { };

    const_ref<int>& operator=(const const_ref<int>& eq) {
	ref_var = eq.ref_var;
    };

    void print() { std::cout << ref_var << std::endl; }

private:
    const T& ref_var;
};

template<typename T>
const const_ref<T>&& make_cref(const T& ref_var)
{
    const_ref<T> tmp(ref_var);
    return std::move(tmp);
};

void print(int x)
{
    std::cout << x << std::endl;
};

int main()
{
   int x = 5;
   const_ref<int> cref;
   cref = make_cref(x);
   int last_var;
   std::cout << "address of last_var:\t" << &last_var << std::endl;
   std::cout << "address of cref:\t" << &cref << std::endl;
   std::cout << "address of x:\t\t" << &x << std::endl;

    print(x);
    cref.print();

    x = 42;
    print(x);
    cref.print();
};
