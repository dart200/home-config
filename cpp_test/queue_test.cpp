#include<iostream>
#include<list>

int main () {

    std::queue<int> q;

    q.push_back(1);
    q.push_back(2);
    q.push_back(3);
    q.push_back(4);

    std::cout << "loop 1:" << std::endl;

    for (int i : q) {
	std::cout << i << " ";
    }

    std::cout << std::endl;

    std::cout << "loop 2:" << std::endl;

    for (int i : q) {
	std::cout << i << " ";
    }

    std::cout << std::endl;

    std::cout << "loop 3:" << std::endl;

    for (int i : q) {
	std::cout << i << " ";
    }

    std::cout << std::endl;
}
