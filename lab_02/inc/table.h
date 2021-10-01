#ifndef __TABLE_H__
#define __TABLE_H__

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
void table_print(table_t *self);
void table_update_keys(table_t *self, int type);
void table_sort_keys(table_t *self);
void table_print_proxy(table_t *self);

#endif // !__TABLE_H__