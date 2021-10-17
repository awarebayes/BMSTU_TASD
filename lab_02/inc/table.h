#ifndef __TABLE_H__
#define __TABLE_H__

#define _GNU_SOURCE 
#include "book.h"
#include "key.h"

typedef struct 
{
    book_t *books;
    book_key_t *keys;
    int size;
    int capacity;
} table_t;


table_t table_new(int size);
void table_delete(table_t *self);
table_t table_realloc(table_t *self, int new_size);
void table_insert(table_t *self, book_t book);
table_t table_read_file(FILE *fin, int n, int *ec);
void table_serialize_file(table_t *self, FILE *fout);
void table_print(table_t *self);
void table_print_at_indexes(table_t *self, int *indexes, int n);
void table_update_keys(table_t *self);
void table_sort_keys(table_t *self, sort_func_t sort);
void table_sort(table_t *self, sort_func_t sort);
void table_print_proxy(table_t *self);
void table_print_key_table(table_t *self);
int *table_filter(table_t *self, book_key_t *key, int *n);
void table_remove(table_t *self, int *indexes, int n);
int *table_filter_tech_year(table_t *self, int year, char *field, int *n);
size_t table_size(table_t *self);
size_t table_keys_size(table_t *self);

#endif // !__TABLE_H__