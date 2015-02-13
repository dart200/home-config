#include <malloc.h>
#include <iostream>
#include <cassert>

int main()
{
    for (int i = 1; i < (1 << 10); i++) {
	void* p = aligned_alloc(i, 5 << 10);
	free(p);
    }

    size_t alignment = (4<<10) + 34;

    void* p = aligned_alloc(alignment, 5 << 10);
    void* p2 = aligned_alloc(alignment, 10 << 10);

    assert(p && p2);

#define CHUNK_SZ_MASK (~(sizeof(size_t) - 1))
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
}
