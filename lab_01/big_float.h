#ifndef __BIG_FLOAT__
#define __BIG_FLOAT__

#include "big_int.h"

#define MAX_EXP 99999

typedef struct
{
    big_int_t m;
    int32_t exp;
} big_float_t;

void bf_print(big_float_t *b);
big_float_t bf_read(int *ec);
big_float_t bf_sread(char *buf, int *ec);
big_float_t bf_sum(big_float_t *a, big_float_t *b);
big_float_t bf_sub(big_float_t *a, big_float_t *b);
big_float_t bf_mul(big_float_t *self, big_float_t *other, int *ec);
big_float_t bf_int_div_f(big_int_t self, big_float_t other, int *ec);
void bf_normalize(big_float_t *self);
int bf_exact_eq(big_float_t *a, big_float_t *b);

#endif