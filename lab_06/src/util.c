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

char *rand_string(char *str, int size)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
	if (size) {
		--size;
		for (int n = 0; n < size; n++) {
			int key = rand() % (int) (sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}

// hash function: http://www.cse.yorku.ca/~oz/hash.html#djb2
int djb2(void *data)
{
	unsigned char *str = data;
	int hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash;
}

// hash function: http://www.cse.yorku.ca/~oz/hash.html#sdbm
int sdbm(void *data)
{
	unsigned char *str = data;
	int hash = 0;
	int c;
	while ((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;
	return hash;
}
