
#include <iostream>
#include <mutex>

class obj
{
public:
    int x = 0;

    obj() {
	std::cout << "default ctr" << std::endl;
    };

    obj(int init) : x(init) {
	std::cout << "init ctr" << std::endl;
    };

    obj(obj& copy) : x(copy.x) {
	std::cout << "copy ctr" << std::endl;
    };

    obj(obj&& move_from) : x(move_from.x) {
	move_from.x = 0;
	std::cout << "move ctr" << std::endl;
    };

    static obj create_rvo(int init) {
	return obj(init);
    };

    static obj create_move(int init) {
	return std::move(obj(init));
    };

    static obj&& create_move_ref(int init) {
	return std::move(obj(init));
    };

    //static obj&& create_move_ref2(int init) {
    //	return obj(init);
    //};

    static obj&& create_copy_val(obj copy_from) {
	return std::move(copy_from);
    }

    static obj create_copy_ptr(obj* init) {
	return obj(*init);
    }

    static obj&& create_copy_ref(obj& init) {
    }

    static obj&& create_copy_xref(obj&& init) {
    }
};

int main()
{
    std::cout << "x1:" << std::endl;
    obj x1;

    std::cout << "\nx2:" << std::endl;
    obj x2(5);

    std::cout << "\nx3:" << std::endl;
    obj x3(x2);

    std::cout << "\nx4:" << std::endl;
    obj x4 = obj::create_rvo(42);

    std::cout << "\nx5:" << std::endl;
    obj x5 = obj::create_move(42);

    std::cout << "\nx6:" << std::endl;
    obj x6 = obj::create_move_ref(420);

    std::cout << "\nx7:" << std::endl;
    obj x7 = obj::create_copy_val(x6);

    std::cout << "\nx8:" << std::endl;
    obj x8 = obj::create_copy_val(x6);
};
