#include <stdio.h>
#include "util.c"
#include "big_int.c"
#include "big_float.c"
#include "unit_tests.c"

int main()
{
    //run_tests();
    int ec = 0;
    big_int_t a = {0};
    big_float_t b = {0};
    big_float_t res = {0};

    banner();
    ruller();
    a = bi_read(&ec);
    ruller();
    b = bf_read(&ec);
    if (!ec)
    {
        res = bf_int_div_f(a, b, &ec);
        printf("  ");
        ruller();
        bf_print(&res);
    }
    print_ec(ec);
    return ec;
}