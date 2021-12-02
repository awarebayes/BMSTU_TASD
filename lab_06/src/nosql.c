//
// Created by dev on 12/2/21.
//

#include "nosql.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 1024
#define RAND_STR_BUF_SIZE 128

int nosql_search(FILE *f, char *key, int *cmps, int *ec)
{
	int local_ec = 0;
	if (!f)
		local_ec = 1;
	char temp[BUF_SIZE];
	while (!feof(f) && !local_ec)
	{
		if (fscanf(f, "%s", temp) != 1)
			local_ec = 1;
		if (cmps)
			(*cmps)++;
		if (strcmp(temp, key) == 0)
			return 1;
	}
	fclose(f);
	if (ec)
		*ec = local_ec;
	return 0;
}

void nosql_random(FILE *f, int size, char *random_word)
{
	int added = 0;
	int random_word_idx = rand() % size;

	char buf[RAND_STR_BUF_SIZE];
	while (added < size)
	{
		rand_string(buf, RAND_STR_BUF_SIZE);
		if (random_word_idx == added)
			strcpy(random_word, buf);
		fprintf(f, "%s\n", random_word);
		added++;
	}
}
