#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 256

typedef int (*cmp_func_t)(const void *, const void *);
typedef void (*sort_func_t)(void *base, size_t nmemb, size_t size, cmp_func_t);
typedef int (*measure_f)(int size, sort_func_t sort);

int str_cmp(const void *a, const void *b);
int int_cmp(const void *a, const void *b);
void memswap(void *m1, void *m2, size_t size);
void insert_sort(void *base, size_t nmember, size_t size, cmp_func_t cmp);
void read_str(FILE *fout, char *hint_msg, char *target, FILE *fin, int *ec);
void read_int(FILE *fout, char *hint_msg, int *target, FILE *fin, int *ec);
char *rand_string(char *str, size_t size);
int sorting_time_table_ns(int size, sort_func_t sort);
int sorting_time_keys_ns(int size, sort_func_t sort);
int sorting_time_mean(measure_f measure, sort_func_t func, int size, int times);
int64_t ticks(void);

#endif // !__UTIL_H__