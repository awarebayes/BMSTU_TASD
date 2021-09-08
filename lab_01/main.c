#include <stdio.h>
#include "big_int.h"

int main()
{
    int ec = 0;
    big_int_t a = bi_read(&ec);
    big_int_t b = bi_read(&ec);
    big_int_t c = bi_sum(&a, &b, &ec);
    bi_print(&c);
}