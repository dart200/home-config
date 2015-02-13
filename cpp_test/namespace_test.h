
#include <exception>

namespace motherbitch
{
    class exception : public std::exception
    {
	const char* what() const noexcept {
	    return "EXCEPTION MOTHER BITCH";
	}
    };

    void my_func();
}

// vim: ft=cpp
