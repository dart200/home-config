
#include <vector>
#include <iostream>
#include <unordered_set>

int main() {

    int a, b, c, d;
    std::unordered_set<int*> vec {&a, &b, &c, &d};

    auto begin = vec.begin();
    std::cout << "size of iterator:" << sizeof(begin) << std::endl;
}
