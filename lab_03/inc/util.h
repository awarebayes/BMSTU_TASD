#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdint.h>
#include "cons.h"

#define SSIZE 64
#define BUFFER_SIZE 256
// #define DEBUG

enum err_enum
{
    ok,
    input_err,
    file_err,
};

void read_str(FILE *fin, FILE *fout, char *hint_msg, char *target, int *ec);
void read_int(FILE *fin, FILE *fout, char *hint_msg, int *target, int *ec);
int *read_arr(FILE *fin, FILE *fout, char *hint_msg, int n, int *ec);
void read_three_ints(FILE *fin, FILE *fout, char *hint_msg, int *a, int *b, int *c, int *ec);
cons_t *read_arr_cons(FILE *fin, FILE *fout, char *hint_msg);

#endif // !__UTIL_H__