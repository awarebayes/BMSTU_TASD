#include "big_int.h"
#include "util.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 64


big_int_t bi_read(int *ec)
{
    char buf[BUF_SIZE] = {0};
    fgets(buf, BUF_SIZE, stdin);
    // may be a problem here
    return bi_sread(buf, ec);
}

big_int_t bi_sread(char *buf, int *ec)
{
    big_int_t self = {0};

    clear_lc(buf);
    ignore_whitespace(&buf);
    if (strlen(buf) == 0)
        *ec = read_err;

    while (*buf == '0')
        buf++;

    if (*buf == '+' || *buf == '-')
    {
        self.sign = (*buf == '-');
        buf++;
    }

    if (!no_bad_chars(buf))
    {
        *ec = read_err;
        return self;
    }

    int buf_len = n_char_digits(buf);

    if (buf_len > MAX_BI_CHAR)
    {
        *ec = num_too_long_err;
        return self;
    }

    if (buf_len <= N_CHARS_PART) // one part
    {
        sscanf(buf, "%ld", &self.p2);
    }
    else  // two parts
    {
        int offset = buf_len - N_CHARS_PART;
        sscanf(buf + offset, "%ld", &self.p2);
        // idk why but
        // buf + offset = '\0'
        // gives segfault
        char *temp = malloc(sizeof(char) * BUF_SIZE);
        strncpy(temp, buf, offset);
        sscanf(temp, "%ld", &self.p1);
        free(temp);
    }
    
    return self;
}

void bi_sprint(big_int_t *self, char *buf)
{
    char sign = self->sign ? '-' : '+';
    if (self->p1)
    {
        sprintf(buf, "%c%ld%015ld", sign, self->p1, self->p2);
    }
    else
        sprintf(buf, "%c%ld", sign, self->p2);
}

void bi_print(big_int_t *self)
{
    char buf[64];
    bi_sprint(self, buf);
    printf("%s\n", buf);
}

// p1 larger then p2
// p1 smaller then p2
int bi_cmp(big_int_t *self, big_int_t *other)
{
    if (self->sign != other->sign)
    {
        if (!self->sign && other->sign)
            return lg;
        return sm;
    }
    if (self->p1 > other->p1)
        return lg;
    else if (self->p1 < other -> p1)
        return sm;
    else {
        if (self->p2 > other->p2)
            return lg;
        else if (self->p2 < other -> p2)
            return sm;
    }
    return eq;
}

big_int_t bi_sum(big_int_t *self, big_int_t *other, int *ec)
{
    big_int_t res = {0};
    if (self->sign != other->sign)
    {
        //if (self->sign) // -3 + 4
        //    return bi_sub(other, self, ec); // 4 - 3
        //else // 4 - 3
        //    return bi_sub(self, other, ec); // 4 - 3
        perror("Multisign bad!\n");
    }

    res.p2 = self->p2 + other->p2;
    res.p1 = self->p1 + other->p1;
    if (res.p2 >= DIGIT_BORROW)
    {
        res.p2 -= DIGIT_BORROW;
        res.p1 += 1;
        if (res.p1 > MAX_PART)
            *ec = overflow_err;
    }

    return res;
}

big_int_t bi_lshift(big_int_t *self, int *ec)
{
    big_int_t res = *self;
    res.p2 *= 10;
    int carry = 0;
    if (res.p2 > MAX_PART)
    {
        carry = res.p2 / DIGIT_BORROW;
        res.p2 %= DIGIT_BORROW;
    }
    res.p1 *= 10;
    res.p1 += carry;
    if (res.p1 > MAX_PART)
        *ec = overflow_err;
    return res;
}

big_int_t bi_rshift(big_int_t *self)
{
    big_int_t res = *self;
    res.p2 /= 10;
    int carry = res.p1 % 10;
    res.p1 /= 10;
    res.p2 += (DIGIT_BORROW / 10) * carry;
    return res;
}

big_int_t bi_sub(big_int_t *self, big_int_t *other, int *ec)
{
    // todo add sign handling
    big_int_t res = *self;
    res.p2 = self->p2 - other->p2;

    if (!self->p1 && !other->p1)
    {
        if (res.p2 < 0)
        {
            res.p2 *= -1;
            res.sign = !res.sign;
        }
    }
    else 
    {
        if (res.p2 < 0)
        {
            perror("Careful here it does not work");
            res.p2 += DIGIT_BORROW;
            res.p1 -= 1;
        }

        res.p1 = self->p1 - other->p1;
        if (res.p1 < 0)
        {
            res.p1 *= -1;
            res.sign = !res.sign;
        }
    }
    return res;
}

big_int_t bi_mul_dec(big_int_t *self, int other, int *ec)
{
    big_int_t res = {0};

    if (!(other >= 0 && !self->sign))
    {
        perror("Unhandled short mul dec");
        *ec = bad_internal_op_err;
    }

    res.p2 = self->p2 * (int64_t)other;
    if (res.p2 < 0)
        *ec = overflow_err;

    res.p1 = self->p1 * (int64_t)other;

    if (res.p2 > MAX_PART)
    {
        int carry = res.p2 / DIGIT_BORROW;
        res.p2 -= DIGIT_BORROW * carry;
        res.p1 += carry;
        if (res.p1 > MAX_PART)
            *ec = overflow_err;
    }

    return res;
}

int get_first_digit(big_int_t *self, int *ended)
{
    if (self->p1 == 0 && self->p2 == 0)
        *ended = 1;
    return self->p2 % 10;
}

big_int_t bi_mul(big_int_t self, big_int_t by, int *ec)
{
    big_int_t res = {0};
    big_int_t temp = {0};

    if (!(!by.sign  && !self.sign))
    {
        perror("Unhandleded long mul dec\n");
        *ec = bad_internal_op_err;
    }

    int by_ended = 0;
    while (!by_ended && !(*ec))
    {
        temp = bi_mul_dec(&self, get_first_digit(&by, &by_ended), ec);
        res = bi_sum(&res, &temp, ec);
        by = bi_rshift(&by);
        self  = bi_lshift(&self, ec);
    }

    return res;
}
