#include "util.h"
#include "book.h"
#include "table.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SORTING_TYPE 1

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

void read_str(FILE *fout, char *hint_msg, char *target, FILE *fin, int *ec)
{
    if (fout)
        fprintf(fout, "%s", hint_msg);
    fgets(target, BUFFER_SIZE, fin);
    if (strcmp(target, "\n") == 0)
        fgets(target, BUFFER_SIZE, fin);
    if (strlen(target) >= SSIZE)
        *ec = input_err;
    if (ferror(fin))
        *ec = input_err;
    else
    {
        char *newline = strchr(target, '\n');
        if (newline != NULL)
            *newline = '\0'; // delete \n
    }
}

void read_int(FILE *fout, char *hint_msg, int *target, FILE *fin, int *ec)
{
    char buffer[BUFFER_SIZE];
    char temp[BUFFER_SIZE];
    int tempint;
    if (fout)
        fprintf(fout, "%s", hint_msg);
    fgets(buffer, BUFFER_SIZE, fin);
    if (sscanf(buffer, "%d", target) != 1)
        *ec = input_err;
    if (sscanf(buffer, "%d %s", &tempint, temp) == 2)
        *ec = input_err;
    if (*target < 0)
        *ec = input_err;
}

char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK .!@#$";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = random() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

int sorting_time_table_ns(int size, sort_func_t sort)
{
    table_t table = table_new(size);
    for (int i = 0; i < size; i++)
        table_insert(&table, book_random());

    int64_t start = ticks();
    table_sort(&table, sort, SORTING_TYPE);
    int64_t end = ticks();
    //int ns = (end - start) * 1000000 / CLOCKS_PER_SEC;
    int ns = end - start;
    table_delete(&table);
    return ns;
}

int sorting_time_keys_ns(int size, sort_func_t sort)
{
    table_t table = table_new(size);
    for (int i = 0; i < size; i++)
        table_insert(&table, book_random());
    table_update_keys(&table, SORTING_TYPE);

    int64_t start = ticks();
    table_sort_keys(&table, sort);
    int64_t end = ticks();
    int ns = end - start;
    table_delete(&table);
    return ns;
}


int sorting_time_mean(measure_f measure, sort_func_t func, int size, int times)
{
    long int sum = 0;
    for (int i = 0; i < times; i++)
    {
        sum += (long int)measure(size, func);
    }
    return (int)(sum / (long int)times);
}

int64_t ticks(void)
{
    int32_t h, l;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (h), "=r" (l)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    int64_t t = ((int64_t)h << 32) | l;
    return t;
}