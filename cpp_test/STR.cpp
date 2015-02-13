
#include <iostream>

#define STR(x) (#x)

template<typename T>
class foo
{
public:
    const char* bar() {
	return STR(T);
    }
};

int main()
{
    std::cout << STR(what) << std::endl;
    std::cout << foo<char>().bar() << std::endl;
}
