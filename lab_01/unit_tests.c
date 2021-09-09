#include <assert.h>
#include <string.h>
#include "big_int.h"


void big_int_read()
{
    int ec = 0;
    big_int_t a = bi_sread("12345", &ec);
    big_int_t target = {.p1=0, .p2=12345, .sign=0};
    assert(ec == 0);
    assert(memcmp(&a, &target, sizeof(target)) == 0);
}



int run_tests(void)
{
    big_int_read();
    return 0;
}