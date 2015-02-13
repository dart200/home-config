
#include <malloc.h>
#include <new>
#include <iostream>
#include <cassert>

#define CHUNK_SZ_MASK (~(sizeof(size_t) - 1))

void malloc_explore()
{
    std::cout << "malloc_explore:" << std::endl;

    size_t alignment = (4<<10);

    void* p = aligned_alloc(alignment, 5 << 10);
    void* p2 = aligned_alloc(alignment, 10 << 10);

    assert(p && p2);

    size_t* chunk = ((size_t*)p - 1);
    size_t chunk_size = chunk[0] & CHUNK_SZ_MASK;
    size_t* next_chunk = chunk + (chunk_size/sizeof(size_t)) - 1;
    size_t chunk_size_end = next_chunk[0] & CHUNK_SZ_MASK;
    size_t chunk_size_next = next_chunk[1] & CHUNK_SZ_MASK;

    std::cout << "\nalignment: " << alignment
              << "\nmin align: " << __alignof__(long double)
              << "\nlen size_t: " << sizeof(size_t)
              << "\nusage_size(): " << malloc_usable_size(p)
              << "\nchunk1 size: " << chunk_size
              << "\nchunk1 size@end: " << chunk_size_end
              << "\nchunk2 size: " << chunk_size_next
              << "\np: " << p
              << "\np2: " << p2
              << "\np2 - p1: " << (char*)p2 - (char*)p
              << std::endl;

    for (int i = 1; i < (1 << 10); i++) {
	void* p = aligned_alloc(i, 5 << 10);
	free(p);
    }

    std::cout << std::endl;
}

void die (std::string error_str)
{
    std::cerr << error_str << std::endl;
    exit(EXIT_FAILURE);
}

void print_malloced_size(void* p)
{
    size_t* chunk = ((size_t*)p - 1);
    size_t chunk_size = chunk[0] & CHUNK_SZ_MASK;
    size_t malloced_size = chunk_size - sizeof(size_t);

    std::cout << "mallocated size: " << malloced_size << " bytes" << std::endl;
}

class obj
{
public:
    char buf[32];

    void* operator new (size_t sz)
    {
	void* p = ::operator new(sz);
	std::cout << "new - size: " << sz << " p: " << p << std::endl;
	return p;
    }

    void* operator new[] (size_t sz)
    {
	void* p = ::operator new(sz);
	std::cout << "new[] - size: " << sz << " p: " << p << std::endl;
	return p;
    }

    obj() { };
    ~obj() {
	std::cout << "destructor call" << std::endl;
    };
};

void new_explore()
{
    std::cout << "newing obj - size: " << sizeof(obj) << std::endl;
    obj* o1 = new obj();
    std::cout << "returned ptr: " << o1 << std::endl;

    const int len = 4;
    std::cout << "newing obj[] - size: " << sizeof(obj) * len << std::endl;
    obj* o2 = new obj[len];
    std::cout << "returned ptr: " << o2 << std::endl;
    std::cout << "array size: " << *(reinterpret_cast<size_t*>(o2) - 1) << std::endl;

    delete o1;
    delete[] o2;

    std::cout << std::endl;
}

int main()
{
    malloc_explore();
    new_explore();
}
