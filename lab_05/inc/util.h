//
// Created by dev on 11/3/21.
//

#ifndef LAB_05_UTIL_H
#define LAB_05_UTIL_H

#include <stdio.h>
#include <inttypes.h>

#define  BUFFER_SIZE 256

enum err_enum
{
	ok,
	input_err,
	file_err,
};

void memswap(void* a, void* b, size_t size);
float rand_float(float low, float high);
void read_int(FILE *fin, FILE *fout, char *hint_msg, int *target, int *ec);
void read_float(FILE *fin, FILE *fout, char *hint_msg, float *target, int *ec);
uint64_t ticks(void);

#endif //LAB_05_UTIL_H
