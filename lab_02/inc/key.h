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
int key_cmp(void *a, void *b);
int get_base_type(int key_type);

#endif // !__KEY_H__