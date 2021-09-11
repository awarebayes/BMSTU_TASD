#include "util.h"
#include <ctype.h>
#include <string.h>
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