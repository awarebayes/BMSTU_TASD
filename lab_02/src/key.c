#include "book.h"
#include <assert.h>

int key_cmp(const void *a, const void *b)
{
    book_key_t *k1 = (book_key_t *)a;
    book_key_t *k2 = (book_key_t *)b;
    assert(k1->type == k2->type);
    switch (k1->base_type)
    {
    case key_string:
        return str_cmp(k1->key, k2->key);
    case key_int:
        return int_cmp(k1->key, k2->key);
    }
}

char *show_key(char *buf, book_key_t *key)
{
    switch (key->base_type)
    {
    case key_string:
        sprintf(buf, "%s", key->key);
        break;
    case key_int:
        sprintf(buf, "%d", key->key);
        break;
    }
    return buf;
}

book_key_t key_new(int type, void* key, int pos_actual)
{
    book_key_t self = {0};
    self.type = type;
    self.base_type = get_base_type(type);
    self.pos_actual = pos_actual;
    self.pos_fake = pos_actual;
    self.key = key;
    return self;
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