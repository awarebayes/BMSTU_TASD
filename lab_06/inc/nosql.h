//
// Created by dev on 12/2/21.
//

#ifndef LAB_06_NOSQL_H
#define LAB_06_NOSQL_H

#include "stdio.h"

void nosql_random(FILE *f, int size, char *random_word);
int nosql_search(FILE *f, char *key, int *cmps, int *ec);

#endif //LAB_06_NOSQL_H
