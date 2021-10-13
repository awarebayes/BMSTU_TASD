#include "cons.h"
#include <stdio.h>
#include <stdlib.h>


void cons_delete(cons_t *self)
{
    cons_t *prev = NULL;
    while (self != NULL)
    {
        prev = self;
        self = self->next;
        free(prev);
    }
}

cons_t *cons_new(int value)
{
    cons_t *self = (cons_t*)malloc(sizeof(cons_t));
    self->value = value;
    self->next = NULL;
    return self;
}

void cons_add(cons_t *self, int value)
{
    while (self->next != NULL)
        self = self->next;
    cons_t *new_cons = (cons_t*)malloc(sizeof(cons_t));
    self->next = new_cons;
    new_cons->value = value;
    new_cons->next = NULL;
}

int cons_get(cons_t *self, int idx)
{
    int n = 0;
    while (n < idx)
    {
        self = self->next;
        n++;
    }
    return self->value;
}

size_t cons_size(cons_t *self)
{
  size_t res = 0;
  if (self != NULL) {
    res = sizeof(int *) + sizeof(int);
    if (self->next != NULL)
      res += cons_size(self->next);
  }
  return res;
}
