
#include <iostream>
#include <unordered_map>

int main (int argc, char* argv[])
{
    std::unordered_map<uint64_t, void*> m;

    void* search = m[42];

    std::cout << "ptr: " << search << std::endl;

    if (search == nullptr) {
	std::cout << "true" << std::endl;
    }
}
