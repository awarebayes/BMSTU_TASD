#include <stdio.h>
#include "util.h"
#include "big_int.h"
#include "big_float.h"
//#include "unit_tests.h"

int main()
{
    //run_tests();
    int ec = 0;
    big_int_t a = bi_sread("12345", &ec);
    bi_print(&a);
    return ec;
}