
#include "overload_lookup.h"

#include <iostream>

struct A {
    void* operator new(size_t sz) {
	std::cout << "using A's new" << std::endl;
	return ::operator new(sz);
    };

    void operator delete(void* p) {
	std::cout << "using A's delete" << std::endl;
	::operator delete(p);
    }

    static int* new_int(const int init_val = 0) {
	return new int(init_val);
    }

    ptr<int> int_ptr();
    ptr<char> char_ptr();
};

struct B {
    void* operator new(size_t sz) {
	std::cout << "using B's new" << std::endl;
	return ::operator new(sz);
    };

    void operator delete(void* p) {
	std::cout << "using B's delete" << std::endl;
	::operator delete(p);
    }

    ptr<int> int_ptr();
    ptr<unsigned> unsigned_ptr();
};

int main() {
    int i = 1;
    char c = 'a';
    unsigned u = 1;

    A a();
    B b();

    int* A_i = A::new_int(5);
    std::cout << "A_i: " << *A_i << std::endl;
};

