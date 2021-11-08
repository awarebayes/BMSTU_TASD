//
// Created by dev on 11/3/21.
//

#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t ticks(void)
{
	unsigned long long tmp;
	__asm__ __volatile__ ("rdtsc" : "=A" (tmp));
	return tmp;
}

void memswap(void *a, void *b, size_t size)
{
	char *a_swap = (char *) a, *b_swap = (char *) b;
	char *a_end = (char *) a + size;

	while (a_swap < a_end)
	{
		char temp = *a_swap;
		*a_swap = *b_swap;
		*b_swap = temp;

		a_swap++, b_swap++;
	}
}


float rand_float(float low, float high)
{
	float rfloat = (float) rand() / (float) (RAND_MAX / 1.0);
	float limited = (high - low) * rfloat + low;
	return limited;
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


void read_float(FILE *fin, FILE *fout, char *hint_msg, float *target, int *ec)
{
	char buffer[BUFFER_SIZE];
	char temp[BUFFER_SIZE];
	float temp_int = 0;
	if (fout)
		fprintf(fout, "%s", hint_msg);
	fgets(buffer, BUFFER_SIZE, fin);
	if (sscanf(buffer, "%f", target) != 1)
		*ec = input_err;
	if (sscanf(buffer, "%f %s", &temp_int, temp) == 2)
		*ec = input_err;
	if (strcmp(buffer, "\n") == 0)
		fgets(buffer, BUFFER_SIZE, fin);
	if (*target < 0)
		*ec = input_err;
}
