//
// Created by dev on 12/13/21.
//
#include "semiring.h"
#define MAX(a,b) a > b ? a : b
#define MIN(a,b) a < b ? a : b

int R_minus_add(int a, int b)
{
	return MAX(a, b);
}

int R_minus_multiply(int a, int b)
{
	return a + b;
}

int R_plus_add(int a, int b)
{
	return MIN(a, b);
}

int R_plus_multiply(int a, int b)
{
	if (a == INT_MAX || b == INT_MAX)
		return INT_MAX;
	return a + b;
}


int B_add(int a, int b)
{
	return MIN(a, b);
}

int B_multiply(int a, int b)
{
	if (a == INT_MAX || b == INT_MAX)
		return INT_MAX;
	return a + b;
}
