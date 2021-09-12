#ifndef __UTIL_H__
#define __UTIL_H__



enum errors
{
    ok,
    num_too_long_err,
    bad_chars_err,
    overflow_err,
    bad_internal_op_err,
    read_err,
    zero_div_err,
};

enum ord
{
    eq,
    lg,
    sm,
};

int n_digits(int n);
void clear_lc(char *s);
void ignore_whitespace(char **s);
int n_char_digits(char *s);
void strdel(char *begin, int index);
int no_bad_chars(char *s);
int n_char_digits_ignore_end_zero(char *s);
void banner();
void ruller();
void print_ec(int ec);

#endif