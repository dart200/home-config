
#include <string>
#include <iostream>

using std::cout;

enum class int_enum : uint64_t
{
    FOO = 1,
    BAR = 2,
};

int main ()
{
    int_enum i = int_enum::FOO;

    cout << "size of int_enum: " << sizeof(i) << std::endl;
    cout << "current val of i: " << static_cast<int>(i) << std::endl;;
}
