#include "big_float.h"
#include "big_int.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 64


big_float_t bf_read(int *ec)
{
    char buf[BUF_SIZE] = {0};
    fgets(buf, BUF_SIZE, stdin);
    return bf_sread(buf, ec);
}

big_float_t bf_sread(char *buf, int *ec)
{
    big_float_t self = {0};
    clear_lc(buf);
    ignore_whitespace(&buf);

    if (strlen(buf) == 0)
        *ec = read_err;

    // exponent processing
    char *exponent_ptr = strchr(buf, 'E');
    if (exponent_ptr != NULL)
    {
        exponent_ptr++; // move from E
        ignore_whitespace(&exponent_ptr);
        if (!no_bad_chars(exponent_ptr))
            *ec = read_err;
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

void bf_minmax_exp(big_float_t *min, big_float_t *max)
{
    big_float_t temp;
    if (min->exp > max->exp)
    {
        temp = *min;
        *min = *max;
        *max = temp;
    }

}

void bf_normalize_max(big_float_t *a, big_float_t *b, int *ec)
{
    bf_minmax_exp(a, b); // b > a
    big_float_t b_copy = *a;

    while (a->exp != b->exp)
    {
        b->exp--;
        bi_lshift(&b->m, ec);
    }
    if (*ec == overflow_err)
        *b = b_copy;
}

big_float_t bf_sum(big_float_t *a, big_float_t *b)
{
    int ec = 0;
    big_float_t res = {0};

    bf_minmax_exp(a, b);
    bf_normalize_max(a, b, &ec);
    if (ec == overflow_err)
    {
        ec = ok;
        return *b; // a is too small
    }

    // a == b on scale
    res.m = bi_sum(&a->m, &b->m, ec);
    if (ec == overflow_err)
    // todo rounding
        res.m = bi_rshift(&res.m);
    return res;
}

int bf_exact_eq(big_float_t *a, big_float_t *b)
{
    return bi_cmp(&a->m, &b->m) == eq && a->exp == b->exp;
}