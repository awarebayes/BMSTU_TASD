#include "util.h"
#include <string.h>
#include <stdlib.h>

int str_cmp(const void *a, const void *b)
{
    char *s1 = (char*)a;
    char *s2 = (char*)b;
    return strcmp(s1, s2);
}

int int_cmp(const void *a, const void *b)
{
    int *i1 = (int*)a;
    int *i2 = (int*)b;
    return *i1-*i2;
}

void memswap(void *v1, void *v2, size_t size)
{
    void *temp = malloc(size);
    if (temp != NULL)
    {
        memcpy(temp, v1, size);
        memcpy(v1, v2, size);
        memcpy(v2, temp, size);
        free(temp);
    }
}

// Сортировка выбором
void insert_sort(void *base, size_t nitems, size_t size, int (*cmp)(const void*, const void*))
{
    char *cbase = base;
    for (int j = nitems - 1; j > 0; j--)
    {
        char *max = cbase;
        for (int i = 0; i <= j; i++)
        {
            void *el = cbase + i * size;
            if (cmp(el, max) > 0)
                max = el;
        }
        memswap(max, cbase + size * j, size);
    }
}
