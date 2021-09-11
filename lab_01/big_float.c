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

    //self.exp += n_char_digits(buf);
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

    return self;
}

void bf_print(big_float_t *b)
{
    char mantissa[64];
    bi_sprint(&b->m, mantissa);
    int exp_sub = strlen(mantissa) - 1;
    printf("%c0.%s E %s%d\n", *mantissa, mantissa+1, b->exp > 0 ? "+" : "", b->exp-exp_sub);
}

void bf_minmax_exp(big_float_t *min, big_float_t *max, int *swap_flag)
{
    big_float_t temp;
    if (min->exp > max->exp)
    {
        temp = *min;
        *min = *max;
        *max = temp;
        *swap_flag = 1;
    }
}

void bf_normalize_max(big_float_t *a, big_float_t *b, int *ec)
{
    int swap_flag = 0;
    bf_minmax_exp(a, b, &swap_flag); // b > a
    big_float_t b_copy = *b;

    while (a->exp != b->exp)
    {
        b->exp--;
        b->m = bi_lshift(&b->m, ec);
    }
    if (*ec == overflow_err)
        *b = b_copy;
}

big_float_t bf_sum(big_float_t *a, big_float_t *b)
{
    int ec = 0;
    big_float_t res = {0};
    int swap_flag = 0;
    bf_minmax_exp(a, b, &swap_flag);
    bf_normalize_max(a, b, &ec);
    if (ec == overflow_err)
    {
        ec = ok;
        return *b; // a is too small
    }

    // a == b on scale
    res.m = bi_sum(&a->m, &b->m, &ec);
    res.exp = a->exp;
    if (ec == overflow_err)
    {
        // rounding
        int round = res.m.p2 % 10 > 5;
        res.m = bi_rshift(&res.m);
        res.m.p2 += round;
    }
    bf_normalize(&res);
    return res;
}

big_float_t bf_sub(big_float_t *a, big_float_t *b)
{
    int swap_flag = 0;
    int ec = 0;
    big_float_t res = {0};

    bf_minmax_exp(a, b, &swap_flag);
    bf_normalize_max(a, b, &ec);
    if (ec == overflow_err)
    {
        ec = ok;
        return *b; // a is too small
    }

    // a == b on scale
    res.m = bi_sub(&a->m, &b->m, &ec);
    res.exp = a->exp;
    if (ec == overflow_err)
    {
        // rounding
        int round = res.m.p2 % 10 > 5;
        res.m = bi_rshift(&res.m);
        res.m.p2 += round;
    }
    bf_normalize(&res);
    if (swap_flag)
        res.m.sign = !res.m.sign;
    return res;
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

// does not work
big_float_t bf_mul(big_float_t *self, big_float_t *other, int *ec)
{
    big_float_t res = {0};
    res.exp = self->exp + other->exp;

    int overflow = 0;
    res.m = bi_mul(self->m, other->m, ec, &overflow);

    res.exp += overflow;
    bf_normalize(&res);
    if (res.exp < MAX_EXP && res.exp < -MAX_EXP)
        *ec = overflow_err;
    return res;
}

big_float_t bf_int_div_f(big_int_t self, big_float_t other, int *ec)
{
    big_float_t res = {0};
    res.exp = bi_n_dig(self) - other.exp;
    big_int_t bi_ten = bi_from_int(10);
    big_int_t bi_zero = bi_from_int(0);

    int n = 0;
    big_int_t divident = bi_from_int(0);
    big_int_t remainder = {0};

    // todo add sign handling
    while (bi_n_dig(res.m) < 30 && !(*ec))
    {
        while (bi_cmp(&divident, &other.m) == sm)
        {
            divident = bi_lshift(&divident, ec); 
            big_int_t dig = bi_get_nth_dig_big(self, n);
            n+= 1;
            divident = bi_sum(&divident, &dig, ec);
        }
        int quotient = bi_div_short(divident, other.m, &remainder, ec);
        big_int_t bi_q = bi_from_int(quotient);
        res.m = bi_lshift(&res.m, ec);
        res.m = bi_sum(&res.m, &bi_q, ec);
    }
    
}


int bf_exact_eq(big_float_t *a, big_float_t *b)
{
    return bi_cmp(&a->m, &b->m) == eq && a->exp == b->exp;
}
