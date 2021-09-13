#include <stdio.h>
#include "util.h"
#include "big_int.h"
#include "big_float.h"
#include "unit_tests.h"

int main()
{
    run_tests();
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
    }
    if (!ec)
    {
        printf("  ");
        ruller();
        bf_print(&res);
    }
    print_ec(ec);
    return ec;
}