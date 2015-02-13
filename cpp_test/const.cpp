#include <stdlib.h>
#include <stdio.h>

struct my_struct
{
    int i;
};

void bad_func(const my_struct *s)
{
    s->i = 42;
}

int main()
{
    my_struct s;
    bad_func(&s);

    printf("int value: %d\n", s.i);
}
