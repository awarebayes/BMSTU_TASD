#include "cons.h"

void cons_delete(cons_t *self, int value)
{
    cons_t *next = self->next;
    while (self != NULL)
    {
        free(self)
        self = next;
        cons_t *next = self->next;
    }
}

void cons_add(cons_t *self, int value)
{
    while (self.next != NULL)
        *self = *self.next;
    cons_t new_cons = malloc(sizeof(cons_t));
    new_cons->value = value;
    new_cons->next = NULL;
}

int cons_get(cons_t self, int idx)
{
    int n = 0;
    while (n <= idx)
    {
        self = *self.next;
        n++;
    }
    return self.value;
}