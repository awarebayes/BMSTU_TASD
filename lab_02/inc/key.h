#ifndef __KEY_H__
#define __KEY_H__

typedef struct
{
    int key;
    int pos_actual;
} book_key_t;

book_key_t key_new(int key, int pos_actual);
void key_delete(book_key_t *self);
int key_cmp(const void *a, const void *b);
int get_base_type(int key_type);
char *key_show(book_key_t *self);
book_key_t key_dummy(int key);

#endif // !__KEY_H__