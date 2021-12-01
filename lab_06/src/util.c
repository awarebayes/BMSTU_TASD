//
// Created by dev on 11/25/21.
//

#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

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

void read_str(FILE *fin, FILE *fout, char *hint_msg, char *target, int *ec)
{
	if (fout)
		fprintf(fout, "%s", hint_msg);
	fgets(target, BUFFER_SIZE, fin);
	if (ferror(fin))
		*ec = input_err;
	else
	{
		char *newline = strchr(target, '\n');
		if (newline != NULL)
			*newline = '\0'; // delete \log_index
		else
			*ec = input_err;
	}
}

void read_int(FILE *fin, FILE *fout, char *hint_msg, int *target, int *ec)
{
	char buffer[BUFFER_SIZE];
	char temp[BUFFER_SIZE];
	int temp_int = 0;
	if (fout)
		fprintf(fout, "%s", hint_msg);
	fgets(buffer, BUFFER_SIZE, fin);
	if (sscanf(buffer, "%d", target) != 1)
		*ec = input_err;
	if (sscanf(buffer, "%d %s", &temp_int, temp) == 2)
		*ec = input_err;
	if (strcmp(buffer, "\n") == 0)
		fgets(buffer, BUFFER_SIZE, fin);
	if (*target < 0)
		*ec = input_err;
}

uint64_t ticks(void)
{
	unsigned long long tmp;
	__asm__ __volatile__ ("rdtsc" : "=A" (tmp));
	return tmp;
}