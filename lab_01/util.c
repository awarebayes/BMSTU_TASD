#include "util.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

int n_digits(int n)
{
    int c = 0;
    while (n>0)
    {
        c++;
        n /= 10;
    }
    return c;
}

void clear_lc(char *s)
{
    size_t index = strcspn(s, "\n\r");
    if (index < strlen(s))
        *(s + index) = '\0';
}

void ignore_whitespace(char **s)
{
    while (isspace(**s))
        (*s)++;
}

int n_char_digits(char *s)
{
    int cnt = 0;
    while (isdigit(*(s++)))
        cnt++;
    return cnt;
}

int n_char_digits_ignore_end_zero(char *s)
{
    int cnt = 0;
    int subseq_zero = 0;
    while (isdigit(*s))
    {
        cnt++;
        if (*s=='0')
            subseq_zero++;
        else
            subseq_zero = 0;
        s++;
    }
    return cnt - subseq_zero;
}

void strdel(char *begin, int index)
{
    char *str = begin;
    while (str - begin <= index)
        str++;
    while (*str)
    {
        *(str - 1) = *(str);
        str++;
    }
    *(str-1) = '\0';
}

int no_bad_chars(char *s)
{
    if (*s == '-' || *s == '+')
        s++;
    while (isdigit(*s))
        s++;
    while (isspace(*s))
        s++;
    return *s == '\0';
}

void ruller()
{
    printf("|    |    |    |    |    |    |\n");
}

void banner()
{
    printf("Arbitrary precision division: float / int\n");
    printf("Input float, then input int:\n");
}

void print_ec(int ec)
{
    if (ec)
        printf("An error has arisen: ");
    switch (ec)
    {
        case ok:
            break;
        case num_too_long_err:
            perror("num_too_long_err\n");
            break;
        case bad_chars_err:
            perror("bad_chars_err\n");
            break;
        case overflow_err:
            perror("overflow_err\n");
            break;
        case bad_internal_op_err:
            perror("bad_internal_op_err\n");
            break;
        case read_err:
            perror("read_err\n");
            break;
        case zero_div_err:
            perror("zero_div_err\n");
            break;
        }
}
