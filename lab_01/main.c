#include <stdio.h>
#include "util.c"
#include "big_int.c"
#include "big_float.c"
#include "unit_tests.c"

int main()
{
    run_tests();
    // int ec = 0;
    // big_int_t a = bi_read(&ec);
    // bi_print(&a);
    // return ec;
}