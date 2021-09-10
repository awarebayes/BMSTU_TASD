#ifndef __DATA_H__
#define __DATA_H__
#include <inttypes.h>

#define MAX_BI_CHAR 30
#define N_CHARS_PART 15
#define MAX_PART      999999999999999 
#define DIGIT_BORROW 1000000000000000

typedef struct 
{
    int64_t p1; // part1, 15 chars
    int64_t p2; // part2, 15 chars
    int16_t sign; // sign
} big_int_t;

big_int_t bi_read(int *ec);
big_int_t bi_sread(char *buf, int *ec);
void bi_print(big_int_t *self);
void bi_sprint(big_int_t *self, char *buf);
big_int_t bi_sum(big_int_t *self, big_int_t *other, int *ec);
big_int_t bi_sub(big_int_t *self, big_int_t *other, int *ec);
big_int_t bi_mul_dec(big_int_t *self, int other, int *ec);
int bi_cmp(big_int_t *self, big_int_t *other);
big_int_t bi_lshift(big_int_t *self, int *ec);
big_int_t bi_rshift(big_int_t *self);
big_int_t bi_mul(big_int_t self, big_int_t by, int *ec, int *overflow);
int bi_zero(big_int_t *self);

#endif