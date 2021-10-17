#include "book.h"
#define _GNU_SOURCE 
#include <assert.h>
#include <stdlib.h>
#include <string.h>

book_key_t key_new(int key, int pos_actual)
{
    book_key_t self = {0};
    self.pos_actual = pos_actual;
    self.key = key;
    return self;
}

book_key_t key_dummy(int key)
{
    book_key_t self = {.key = key};
    return self;
}

int key_cmp(const void *a, const void *b)
{
    book_key_t *k1 = (book_key_t *)a;
    book_key_t *k2 = (book_key_t *)b;
    return int_cmp(&k1->key, &k2->key);
}


char *key_show(book_key_t *self)
{
    char *buf = NULL;
    asprintf(&buf, "%d, %d", self->pos_actual, self->key);
    return buf;
}