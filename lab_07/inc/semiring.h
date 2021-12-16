//
// Created by dev on 12/13/21.
//

#ifndef LAB_07_SEMIRING_H
#define LAB_07_SEMIRING_H
#include <limits.h>


typedef struct
{
	int (*add)(int a, int b);
	int (*multiply)(int a, int b);
	int zero;
	int one;
} semiring;

int R_minus_add(int a, int b);
int R_minus_multiply(int a, int b);
int R_plus_add(int a, int b);
int R_plus_multiply(int a, int b);


#endif //LAB_07_SEMIRING_H
