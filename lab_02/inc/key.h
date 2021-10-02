#ifndef __KEY_H__
#define __KEY_H__

enum book_key_type
{
    key_lastname,
    key_title,
    key_publisher,
    key_pages,
    key_type,
};

enum book_key_base_type
{
    key_string,
    key_int
};

typedef struct
{
    void *key;
    int type;
    int base_type;
    int pos_actual;
    int pos_fake;
} book_key_t;

book_key_t key_new(int type, void* key, int pos_actual);
void key_delete(book_key_t *self);
int key_cmp(const void *a, const void *b);
int get_base_type(int key_type);
char *key_show(book_key_t *self);
book_key_t key_dummy(int type, void *key);

#endif // !__KEY_H__