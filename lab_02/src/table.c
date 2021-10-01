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
}

table_t table_realloc(table_t *self, int new_size)
{
    assert(new_size >= self->size);
    table_t new_self = table_new(new_size);
    memcpy(new_self.books, self->books, sizeof(book_t) * self->size);
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

void print_header()
{
    printf("Lastname, title, publisher, pages, type\n");
}

void table_print(table_t *self)
{
    char buf[128];
    printf("Table [%d]:\n", self->size);
    print_header();
    for (int i = 0; i < self->size; i++)
    {
        printf("%s\n", book_show(buf, &self->books[i]));
    }
}

void table_update_keys(table_t *self, int type)
{
    for(int i = 0; i < self->size; i++)
    {

        void *key_ptr = NULL;
        switch (type)
        {
            case key_lastname:
                key_ptr = self->books[i].lastname;
                break;
            case key_title:
                key_ptr = self->books[i].title;
                break;
            case key_publisher:
                key_ptr = self->books[i].publisher;
                break;
            case key_pages:
                key_ptr = &self->books[i].pages;
                break;
            case key_type:
                key_ptr = &self->books[i].type;
                break;
        }
        self->keys[i] = key_new(type, key_ptr, i);
    }
}

