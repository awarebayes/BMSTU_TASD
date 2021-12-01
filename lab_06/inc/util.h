//
// Created by dev on 11/25/21.
//

#ifndef LAB_06_UTIL_H
#define LAB_06_UTIL_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>


enum err_enum
{
	ok,
	input_err,
	file_err,
};

void *xmalloc(size_t size);

void read_str(FILE *fin, FILE *fout, char *hint_msg, char *target, int *ec);

void read_int(FILE *fin, FILE *fout, char *hint_msg, int *target, int *ec);

uint64_t ticks(void);

#endif //LAB_06_UTIL_H
