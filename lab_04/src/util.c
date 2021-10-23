#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>


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

int *read_arr(FILE *fin, FILE *fout, char *hint_msg, int n, int *ec)
{
    int *temp_buf = (int*)malloc(n * sizeof(int));
    int n_scanned = 0;
    if (fout)
        fprintf(fout, "%s", hint_msg);
    for (int i = 0; i < n; i++)
    {
        if (fscanf(fin, "%d", temp_buf + i) == 1)
            n_scanned++;
    }
    if (n_scanned != n)
        *ec = input_err;
    return temp_buf;
}

char *rand_string(size_t size)
{
	char *str = (char *)malloc(size+1);
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK .!@#$";
	if (size) {
		--size;
		for (size_t n = 0; n < size; n++) {
			int key = random() % (int) (sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}

char *rand_palindrome(size_t size)
{
	char *str = rand_string(size);
	size_t even_factor = size % 2;
	size_t middle = size / 2 + even_factor;
	for (size_t i = 0; i < middle; i++)
		str[size - i - 1] = str[i];
	return str;
}

/*
int64_t ticks(void)
{
    int32_t h, l;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (h), "=r" (l)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    int64_t t = ((int64_t)h << 32) | l;
    return t;
}
 */

uint64_t ticks(void)
{
	unsigned long long tmp;
	__asm__ __volatile__ ("rdtsc" : "=A" (tmp));
	return tmp;
}
