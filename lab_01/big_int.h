#ifndef __DATA_H__
#define __DATA_H__
#include <inttypes.h>

#define MAX_BI_CHAR 30
#define N_CHARS_PART 15
#define MAX_PART 999999999999999 

typedef struct 
{
    int16_t sign; // sign
    int64_t p1; // part1, 15 chars
    int64_t p2; // part2, 15 chars
} big_int_t;

big_int_t bi_read(int *ec);
void bi_print(big_int_t *self);
big_int_t bi_sum(big_int_t *self, big_int_t *other, int *ec);

#endif