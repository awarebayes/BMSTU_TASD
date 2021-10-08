#include "table.h"
#include "book.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

table_t table_new(int capacity)
{
    table_t self = {0};
    self.books = calloc(capacity, sizeof(book_t));
    self.keys = calloc(capacity, sizeof(book_key_t));
    self.size = 0;
    self.capacity = capacity;
    return self;
}

void table_delete(table_t *self)
{
    free(self->books);
    free(self->keys);
}

table_t table_realloc(table_t *self, int new_size)
{
    assert(new_size >= self->size);
    table_t new_self = table_new(new_size);
    memcpy(new_self.books, self->books, sizeof(book_t) * self->size);
    memcpy(new_self.keys, self->keys, sizeof(book_key_t) * self->size);
    new_self.size = self->size;
    table_delete(self);
    return new_self;
}

void table_insert(table_t *self, book_t book)
{
    if (self->size+1 >= self->capacity)
        *self = table_realloc(self, self->capacity*2);
    self->books[self->size++] = book;
}

table_t table_read_file(FILE *fin, int n, int *ec)
{
    book_t book = {0};
    table_t table = table_new(1);

    for (int i = 0; i < n; i++)
    {
        book = book_read(fin, NULL, ec);
        table_insert(&table, book);
    }

    return table;
}

void table_serialize_file(table_t *self, FILE *fout)
{
    char buf[1024];
    fprintf(fout, "%d\n", self->size);
    for (int i = 0; i < self->size; i++)
    {
        book_serialize(buf, &self->books[i]);
        fprintf(fout, "%s", buf);
    }
}

void print_header(int index)
{
    if (index)
        printf("index, ");
    printf("pages, type, %-40s, %-30s, %-20s\n", "title", "author", "publisher");
}

void print_keys_header()
{
    printf("pos_fake, pos_actual, value, type\n");
}

void table_print(table_t *self)
{
    if (self->size == 0)
    {
        printf("*Empty table*\n");
        return;
    }
    char buf[256];
    printf("Table [%d]:\n", self->size);
    print_header(1);
    for (int i = 0; i < self->size; i++)
    {
        printf("%-5d, %s\n", i, book_show(buf, &self->books[i]));
    }
}

void table_print_at_indexes(table_t *self, int *indexes, int n)
{
    char buf[256];
    if (n == 0)
    {
        printf("*Empty table*\n");
        return;
    }
    printf("Table, indexed[%d of %d]:\n", n, self->size);
    print_header(1);
    for (int i = 0; i < n; i++)
    {
        int index = indexes[i];
        printf("%-5d, %s\n", index, book_show(buf, &self->books[index]));
    }
}

void table_print_proxy(table_t *self)
{
    if (self->size == 0)
    {
        printf("*Empty table*\n");
        return;
    }
    char buf[256];
    printf("Table [%d]:\n", self->size);
    print_header(1);
    int idx = 0;
    for (int i = 0; i < self->size; i++)
    {
        idx = self->keys[i].pos_actual;
        printf("%-5d, %s\n", idx, book_show(buf, &self->books[idx]));
    }
}

void table_print_key_table(table_t *self)
{
    printf("Key table [%d]:\n", self->size);
    print_keys_header();
    for (int i = 0; i < self->size; i++)
    {
        char *key_str = key_show(&self->keys[i]);
        printf("%d, %s\n", i, key_str);
        free(key_str);
    }
}

size_t table_size(table_t *self)
{
    return self->capacity * sizeof(self->books[0]) + sizeof(self->keys[0]) * self->capacity + sizeof(self->size) + sizeof(self->capacity);
}

size_t table_keys_size(table_t *self)
{
    return sizeof(self->keys[0]) * self->capacity + sizeof(self->size);
}



void table_update_keys(table_t *self, int type)
{
    for(int i = 0; i < self->size; i++)
    {
        self->keys[i] = book_get_key(&self->books[i], type);
        self->keys[i].pos_actual = i;
    }
}

void table_sort_keys(table_t *self, sort_func_t sort)
{
    sort(self->keys, self->size, sizeof(book_key_t), key_cmp);
}

void table_sort(table_t *self, sort_func_t sort, int type)
{
    sort(self->books, self->size, sizeof(book_t), book_cmp_f(type));
}

int *table_filter(table_t *self, book_key_t *key, int *n)
{
    *n = 0;
    int key_type = key->type;
    int *indexes = malloc(self->size * sizeof(int));
    for (int i = 0; i < self->size; i++)
    {
        book_key_t book_key = book_get_key(&self->books[i], key_type);
        if (key_cmp(&book_key, key) == 0)
            indexes[(*n)++] = i;
    }
    return indexes;
}

void table_remove(table_t *self, int *indexes, int n)
{
    table_t new_table = table_new(self->size - n);
    int indexes_index = 0;
    for (int i = 0; i < self->size; i++)
    {
        if (i == indexes[indexes_index])
            indexes_index++;
        else
            table_insert(&new_table, self->books[i]);
    }
    table_delete(self);
    *self = new_table;
}