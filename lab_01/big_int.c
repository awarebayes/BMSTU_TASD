#include "big_int.h"
#include "util.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUF_SIZE 64

big_int_t bi_read(int *ec)
{
    char buf_arr[BUF_SIZE] = {0};
    char *buf = buf_arr;

    fgets(buf, BUF_SIZE, stdin);
    // may be a problem here
    return bi_sread(buf, ec);
}

big_int_t bi_sread(char *buf, int *ec)
{
    big_int_t self = {0};

    clear_lc(buf);
    ignore_whitespace(&buf);
    while (*buf == '0')
        buf++;
        
    if (*buf == '+' || *buf == '-')
    {
        self.sign = (*buf == '-');
        buf++;
    }

    if (!no_bad_chars(buf))
    {
        *ec = bad_chars_err;
        return self;
    }

    int buf_len = strlen(buf);

    if (buf_len > MAX_BI_CHAR)
    {
        *ec = num_too_long_err;
        return self;
    }

    if (buf_len < N_CHARS_PART) // one part
    {
        sscanf(buf, "%ld", &self.p2);
    }
    else  // two parts
    {
        char *offset = buf + buf_len - N_CHARS_PART;
        sscanf(offset, "%ld", &self.p2);
        *offset = '\0';
        sscanf(buf, "%ld", &self.p1);
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
    printf("%s", buf);
}

// p1 larger then p2
// p1 smaller then p2
int bi_cmp(big_int_t *self, big_int_t *other)
{
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

/*
big_int_t bi_sub(big_int_t *self, big_int_t *other, int *ec)
{
    // todo add sign handling
    big_int_t res = *self;
    int need_invert = 0;
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
*/

big_int_t bi_mul_dec(big_int_t *self, int *other, int *ec)
{
    big_int_t res = {0};
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