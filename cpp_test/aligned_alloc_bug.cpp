
#include <unistd.h>
#include <stdlib.h>

const int page_size = getpagesize();
const int alloc_size = 8 << 20;		// 8 MB

int main()
{
    void *p = aligned_alloc(page_size, alloc_size);

    char* char_p = (char*)p;
    for (int i = 0; i < alloc_size; i++) {
	char_p[i] = 'n';
    }
}
