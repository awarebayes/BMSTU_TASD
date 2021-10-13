#ifndef __CONS_H__
#define __CONS_H__

#include <stdio.h>

struct cons_t
{
    int value;
    struct cons_t *next;
};

struct cons_t;
typedef struct cons_t cons_t;

cons_t *cons_new(int value);
void cons_add(cons_t *self, int value);
void cons_delete(cons_t *self);
int cons_get(cons_t *self, int idx);
int cons_next(cons_t *self);
size_t cons_size(cons_t *self);

#endif // !__CONS_H__