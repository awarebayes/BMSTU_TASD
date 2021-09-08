#include "big_int.h"
#include "util.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUF_SIZE 64

void clear_lc(char *s)
{
    *(s + strcspn(s, "\n\r")) = '\0';
}

void ignore_whitespace(char **s)
{
    while (isspace(**s))
        (*s)++;
}

int no_bad_chars(char *s)
{
    while (isdigit(*s))
        s++;
    while (isspace(*s))
        s++;
    return *s == '\0';
}

big_int_t bi_read(int *ec)
{
    big_int_t self = {0};
    char buf_arr[BUF_SIZE] = {0};
    char *buf = buf_arr;

    fgets(buf, BUF_SIZE, stdin);
    clear_lc(buf);
    ignore_whitespace(&buf);
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

void bi_print(big_int_t *self)
{
    char sign = self->sign ? '-' : '+';
    if (self->p1)
        printf("Big int: %c%ld%ld\n", sign, self->p1, self->p2);
    else
        printf("Big int: %c%ld\n", sign, self->p2);
}

big_int_t bi_sum(big_int_t *self, big_int_t *other, int *ec)
{
    // add sign?
    big_int_t res = {0};
    res.p2 = self->p2 + other->p2;
    res.p1 = self->p1 + other->p1;
    if (res.p2 > MAX_PART)
    {
        res.p2 -= MAX_PART;
        res.p1 += 1;
        if (res.p1 > MAX_PART)
            *ec = overflow_err;
    }

    return res;
}