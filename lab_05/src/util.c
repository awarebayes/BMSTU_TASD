//
// Created by dev on 11/3/21.
//

#include "util.h"
#include <string.h>
#include <stdlib.h>

static void swap_byte(void* a, void* b, size_t count)
{
	char* x = (char*) a;
	char* y = (char*) b;

	while (count--) {
		char t = *x; *x = *y; *y = t;
		x += 1;
		y += 1;
	}
}

static void swap_word(void* a, void* b, size_t count)
{
	char* x = (char*) a;
	char* y = (char*) b;
	long t[1];

	while (count--) {
		memcpy(t, x, sizeof(long));
		memcpy(x, y, sizeof(long));
		memcpy(y, t, sizeof(long));
		x += sizeof(long);
		y += sizeof(long);
	}
}

void memswap(void* a, void* b, size_t size)
{
	size_t words = size / sizeof(long);
	size_t bytes = size % sizeof(long);
	swap_word(a, b, words);
	a = (char*) a + words * sizeof(long);
	b = (char*) b + words * sizeof(long);
	swap_byte(a, b, bytes);
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
