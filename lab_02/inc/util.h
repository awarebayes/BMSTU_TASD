#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>

typedef int (*cmp_func_t)(const void *, const void *);
typedef void (*sort_func_t)(void *base, size_t nmemb, size_t size, cmp_func_t);

int str_cmp(const void *a, const void *b);
int int_cmp(const void *a, const void *b);
void memswap(void *m1, void *m2, size_t size);
void insert_sort(void *base, size_t nmember, size_t size, cmp_func_t cmp);

#endif // !__UTIL_H__