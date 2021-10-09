#include "book.h"
#define _GNU_SOURCE 
#include <assert.h>
#include <stdlib.h>
#include <string.h>

book_key_t key_new(int type, void* key, size_t key_size, int pos_actual)
{
    book_key_t self = {0};
    self.type = type;
    self.base_type = get_base_type(type);
    self.pos_actual = pos_actual;
    self.key = malloc(key_size);
    memcpy(&self.key, key, key_size);
    return self;
}

void key_delete(book_key_t *self)
{
    free(self->key);
}

book_key_t key_dummy(int type, void* key)
{
    book_key_t self = {0};
    self.type = type;
    self.base_type = get_base_type(type);
    self.key = key;
    return self;
}

int key_cmp(const void *a, const void *b)
{
    book_key_t *k1 = (book_key_t *)a;
    book_key_t *k2 = (book_key_t *)b;
    // assert(k1->type == k2->type);
    switch (k1->base_type)
    {
    case key_string:
        return str_cmp(k1->key, k2->key);
    case key_int:
        return int_cmp(k1->key, k2->key);
    }
    return 0;
}


char *key_show(book_key_t *self)
{
    char *value = NULL;
    char *buf = NULL;
    switch (self->base_type)
    {
    case key_string:
        asprintf(&value, "%s", (char *)self->key);
        break;
    case key_int:
        asprintf(&value, "%d", *((int*)self->key));
        break;
    }
    asprintf(&buf, "%d, %s, %d", self->pos_actual, value, self->type);
    free(value);
    return buf;
}

int get_base_type(int field_type)
{
    switch (field_type)
    {
    case key_lastname:
    case key_publisher:
    case key_title:
        return key_string;
    case key_pages:
    case key_type:
        return key_int;
    }
    return -1;
}