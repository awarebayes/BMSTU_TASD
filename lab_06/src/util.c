//
// Created by dev on 11/25/21.
//

#include "util.h"
#include <stdlib.h>
#include <stdio.h>

void *xmalloc(size_t size)
{
	void *p = calloc(1, size);
	if (p == NULL)
	{
		printf("xmalloc failed!\n");
		exit(EXIT_FAILURE);
	}
	return p;
}
