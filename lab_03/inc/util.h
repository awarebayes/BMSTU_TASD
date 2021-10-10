#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdint.h>
#include "cons.h"

#define SSIZE 64
#define BUFFER_SIZE 256

enum err_enum
{
    ok,
    input_err,
    file_err,
};

void read_str(FILE *fout, char *hint_msg, char *target, FILE *fin, int *ec);
void read_int(FILE *fout, char *hint_msg, int *target, FILE *fin, int *ec);
int *read_arr(FILE *fout, char *hint_msg, int n, FILE *fin, int *ec);
cons_t *read_arr_cons(FILE *fout, char *hint_msg, FILE *fin);
char *rand_string(char *str, size_t size);
int64_t ticks(void);

#endif // !__UTIL_H__