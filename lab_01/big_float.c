#include "big_float.h"
#include "big_int.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 64
big_float_t bf_read(int *ec)
{
    big_float_t self = {0};
    char buf_arr[BUF_SIZE] = {0};
    char *buf = buf_arr;
    fgets(buf, BUF_SIZE, stdin);
    clear_lc(buf);

    // exponent processing
    char *exponent_ptr = strchr(buf, 'E');
    if (exponent_ptr != NULL)
    {
        exponent_ptr++; // move from E
        ignore_whitespace(&exponent_ptr);
        if (sscanf(exponent_ptr, "%d", &self.exp) != 1)
            *ec = read_err;
        
        *strchr(buf, 'E')= '\0';
    }

    while (*buf == '0')
        buf++;

    // mantissa dot processing
    char *dot_ptr = strchr(buf, '.');
    if (dot_ptr != NULL)
    {
        int to_add_exp = n_char_digits(dot_ptr + 1);
        self.exp -= to_add_exp;
        strdel(buf, dot_ptr - buf);
    }
    self.exp += n_char_digits(buf);

    if (self.exp > MAX_EXP || self.exp < -MAX_EXP)
        *ec = num_too_long_err;

    // mantissa w/o dot
    self.m = bi_sread(buf, ec);

    return self;
}

void bf_print(big_float_t *b)
{
    char mantissa[64];
    bi_sprint(&b->m, mantissa);

    printf("%c0.%s E %s%d\n", *mantissa, mantissa+1, b->exp > 0 ? "+" : "", b->exp);
}