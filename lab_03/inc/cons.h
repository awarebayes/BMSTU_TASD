#ifndef __CONS_H__
#define __CONS_H__

typedef struct
{
    int value;
    struct cons_t *next;
} cons_t;

void cons_add(cons_t *self, int value);

#endif // !__CONS_H__