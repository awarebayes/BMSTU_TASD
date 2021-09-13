#include "big_float.h"
#include "big_int.h"
#include "util.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 64


big_float_t bf_read(int *ec)
{
    char buf[BUF_SIZE] = {0};
    fgets(buf, BUF_SIZE, stdin);
    return bf_sread(buf, ec);
}

big_float_t bf_sread(char *str_ptr, int *ec)
{
    big_float_t self = {0};

    char *buf = malloc(sizeof(char)*BUF_SIZE);
    char *buf_ptr = buf; // to free
    strcpy(buf, str_ptr);

    clear_lc(buf);
    ignore_whitespace(&buf);

    char *old_buf_ptr = buf;

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

    if (*buf == '-' || *buf == '+')
        buf++;

    // mantissa dot processing
    char *dot_ptr = strchr(buf, '.');
    if (dot_ptr != NULL)
    {
        int to_add_exp = n_char_digits_ignore_end_zero(dot_ptr + 1);
        self.exp -= to_add_exp;
        strdel(buf, dot_ptr - buf);
    }

    if (self.exp > MAX_EXP || self.exp < -MAX_EXP)
        *ec = num_too_long_err;

    // mantissa w/o dot
    self.m = bi_sread(old_buf_ptr, ec);
    bf_normalize(&self);

    free(buf_ptr);

    return self;
}

void bf_print(big_float_t *b)
{
    char mantissa[64];
    bi_sprint(&b->m, mantissa);
    int exp_sub = strlen(mantissa) - 1;
    printf("%c0.%s E %s%d\n", *mantissa, mantissa+1, b->exp > 0 ? "+" : "", b->exp+exp_sub);
}

void bf_normalize(big_float_t *self)
{

    if (bi_zero(&self->m))
        self->exp = 0;
    while (self->m.p2 % 10 == 0 && self->m.p2 != 0)
    {
        self->m = bi_rshift(&self->m);
        self->exp++;
    }
}

int normalize_int(big_int_t *self)
{
    int exp = 0;
    while (self->p2 % 10 == 0 && !bi_zero(self))
    {
        exp++;
        *self = bi_rshift(self);
    }
    return exp;
}

int mul_signs_if(big_int_t *self, big_float_t *other)
{
    if ((self->sign && other ->m.sign) || (!self->sign && !other->m.sign))
    {
        return 0;
    }
    self->sign = 0;
    other->m.sign = 0;
    return 1;
}

big_float_t bf_int_div_f(big_int_t a, big_float_t b, int *ec)
{

    big_float_t res = {0};
    if (bi_zero(&b.m))
    {
        *ec = zero_div_err;
        return res;
    }

    // 0 / a
    if (bi_cmp(&a, &res.m) == eq)
    {
        return res;
    }

    int exp = normalize_int(&a);
    res.exp = exp - b.exp;
    int sign = mul_signs_if(&a, &b);

    int n = 0;
    int n_all = bi_n_dig(a);
    big_int_t divident = bi_from_int(0);
    big_int_t remainder = {0};
    while (bi_cmp(&divident, &b.m) == sm)
    {
        divident = bi_lshift(&divident, ec); 
        big_int_t dig = bi_get_nth_dig_big(a, n);
        n+= 1;
        divident = bi_sum(&divident, &dig, ec);
        if (n > n_all + 1)
            res.exp -= 1;
    }
    if (bi_n_dig(divident) == 31)
        *ec = 0;
    while (((bi_n_dig(res.m) < 30 && !bi_zero(&divident)) || n < n_all) && !(*ec))
    {
        int quotient = bi_div_short(divident, b.m, &remainder, ec);
        big_int_t bi_q = bi_from_int(quotient);
        res.m = bi_lshift(&res.m, ec);
        res.m = bi_sum(&res.m, &bi_q, ec);

        big_int_t dig = bi_get_nth_dig_big(a, n);
        n+= 1;
        remainder = bi_lshift(&remainder, ec);
        divident = bi_sum(&remainder, &dig, ec);
        if (n > n_all + 1)
            res.exp -= 1;
        
        if (bi_n_dig(divident) == 31)
            *ec = 0;
    }

    //lets check rounding
    int quotient = bi_div_short(divident, b.m, &remainder, ec);
    if (quotient >= 5)
    {
        // might be overflow error here!
        // 9999999999999999 + 1 kind
        big_int_t one = bi_from_int(1);
        res.m = bi_sum(&res.m, &one, ec);
    }

    if (res.exp > MAX_EXP || res.exp < -MAX_EXP)
        *ec = overflow_err;

    res.m.sign = sign;
    bf_normalize(&res);
    return res;
}


int bf_exact_eq(big_float_t *a, big_float_t *b)
{
    return bi_cmp(&a->m, &b->m) == eq && a->exp == b->exp;
}
