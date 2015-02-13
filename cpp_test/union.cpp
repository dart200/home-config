#include <cstdint>
#include <iostream>

struct foo {
    union {
	uint64_t    ver_1;
	uint32_t    ver_2;
    };
};

int main() {
    foo bar {
	.ver_1 = 1;
    };

    bar.ver_1  = 64;

    std::cout << bar.version.ver_2 << std::endl;

    return 0;
}
