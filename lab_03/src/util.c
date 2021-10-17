#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>


void read_str(FILE *fin, FILE *fout, char *hint_msg, char *target, int *ec)
{
    if (fout)
        fprintf(fout, "%s", hint_msg);
    fgets(target, BUFFER_SIZE, fin);
    if (strcmp(target, "\n") == 0)
        fgets(target, BUFFER_SIZE, fin);
    if (strlen(target) > SSIZE)
        *ec = input_err;
    if (ferror(fin))
        *ec = input_err;
    else
    {
        char *newline = strchr(target, '\n');
        if (newline != NULL)
            *newline = '\0'; // delete \n
    }
}

void read_int(FILE *fin, FILE *fout, char *hint_msg, int *target, int *ec)
{
    char buffer[BUFFER_SIZE];
    char temp[BUFFER_SIZE];
    int tempint;
    if (fout)
        fprintf(fout, "%s", hint_msg);
    fgets(buffer, BUFFER_SIZE, fin);
    if (sscanf(buffer, "%d", target) != 1)
        *ec = input_err;
    if (sscanf(buffer, "%d %s", &tempint, temp) == 2)
        *ec = input_err;
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

void read_three_ints(FILE *fin, FILE *fout, char *hint_msg, int *a, int *b, int *c, int *ec)
{
	char buffer[BUFFER_SIZE];
	char temp[BUFFER_SIZE];
	int tempint;
	if (fout)
		fprintf(fout, "%s", hint_msg);
	fgets(buffer, BUFFER_SIZE, fin);
	if (sscanf(buffer, "%d %d %d", a , b, c) != 3)
		*ec = input_err;
	if (sscanf(buffer, "%d %d %d %s", &tempint, &tempint, &tempint, temp) == 4)
		*ec = input_err;
	if (*a < 0 || * b < 0)
		*ec = input_err;
}

cons_t *read_arr_cons(FILE *fin, FILE *fout, char *hint_msg)
{
    cons_t *res = NULL;
    int temp;
    int local_ec = 0;
    if (fout)
        fprintf(fout, "%s", hint_msg);
    while (!local_ec)
    {
        if (fscanf(fin, "%d", &temp) == 1)
        {
            if (res == NULL)
                res = cons_new(temp);
            else
                cons_add(res, temp);
        }
        else
            local_ec = 1;
    }
    return res;
}

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