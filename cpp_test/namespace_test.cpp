
#include "namespace_test.h"

void motherbitch::my_func()
{
    throw exception();
}

int main(int argc, char* argv[])
{
    motherbitch::my_func();
}
