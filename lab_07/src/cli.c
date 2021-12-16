//
// Created by dev on 12/15/21.
//
#include "matrix.h"
#include "graph.h"
#include "cli.h"
#include <stdint.h>
#include <string.h>

#define EXIT_CHOICE 123
#define BUFFER_SIZE 256
#define BUF_SIZE BUFFER_SIZE
#define TIMES 10

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

int get_choice(int argc, char **argv)
{
	int choice = -1;
	while (choice < 0)
	{
		int ec = 0;
		for (int i = 0; i < argc; i++)
		{
			printf("%d: %s\n", i + 1, argv[i]);
		}
		printf("%d: EXIT\n", EXIT_CHOICE);
		read_int(stdin, stdout, "Your choice: ", &choice, &ec);
		if (ec)
		{
			choice = -1;
			continue;
		}
		if (choice <= 0 || (choice > argc && choice != EXIT_CHOICE))
			choice = -1;
	}
	return choice;
}

void memory_profile()
{
	printf("Memory profile:\n");
	size_t sizes[] = { 10, 100, 500, 1000, 5000, 10000 };
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	printf("|%16s|%16s|\n", "size", "matrix_size");
	for (int i = 0; i < n_sizes; i++)
	{
		size_t size = sizes[i];
		printf("|%16ld", size);;
		printf("|%16ld|\n", size * size);;
	}
}

void speed_profile()
{
	uint32_t sizes[] = { 10, 50, 100, 150 }; // , 5000, 10000 };
	uint64_t start = 0, end = 0;
	uint64_t mean = 0;
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	printf("|%16s|%16s|%16s|\n", "size", "sparsity=30", "sparsity=60");
	semiring R_MINUS = { R_minus_add, R_minus_multiply, .zero=INT_MIN, .one=0 };
	for (int i = 0; i < n_sizes; i++)
	{

		int size = (int) sizes[i];

		printf("|%16d", size);

		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			matrix m_30 = matrix_random(size, 0.3f);
			graph temp = { .adj_mat = m_30 };
			start = ticks();
			floyd_warshall(&temp, &R_MINUS);
			end = ticks();
			mean += end - start;
			matrix_delete(&m_30);
		}

		printf("|%16lu", mean / TIMES);


		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			matrix m_60 = matrix_random(size, 0.6f);
			graph temp = { .adj_mat = m_60 };
			start = ticks();
			floyd_warshall(&temp, &R_MINUS);
			end = ticks();
			mean += end - start;
			matrix_delete(&m_60);
		}

		printf("|%16lu|\n", mean / TIMES);
	}
}

void main_loop()
{

	semiring R_MINUS = { R_minus_add, R_minus_multiply, .zero=INT_MIN, .one=0 };
	semiring R_PLUS = { R_plus_add, R_plus_multiply, .zero=INT_MAX, .one=0 };

	graph orig_graph = graph_new(0);
	graph longest_path_graph = graph_new(0);
	semiring rig = R_MINUS;

	int choice = 0;
	char *choices[] = {
			"[Task]     - run floyd warshall",
			"[Task]     - change semiring",
			"[Profile]  - memory profile",
			"[Profile]  - speed profile on random matrices",
	};

	char *semiring_choices[] = { "R+", "R-" };
	FILE *fin;

	while (choice != EXIT_CHOICE)
	{
		printf("\n");
		choice = get_choice(sizeof(choices) / sizeof(char *), choices);
		printf("\n");
		switch (choice)
		{
			case 1:
				fin = fopen("./res/input.txt", "r");
				orig_graph.adj_mat = matrix_read(fin);
				matrix res = floyd_warshall(&orig_graph, &rig);
				longest_path_graph.adj_mat = res;
				graph_show(&orig_graph, "./res/graph.png");
				graph_show(&longest_path_graph, "./res/longest_path.png");
				matrix_print(&res, stdout);
				fclose(fin);
				break;
			case 2:
				printf("\n");
				choice = get_choice(2, semiring_choices);
				if (choice == 1)
					rig = R_PLUS;
				else
					rig = R_MINUS;
				break;
			case 3:
				memory_profile();
				break;
			case 4:
				speed_profile();
				break;
			default:
				break;
		}
	}

	graph_delete(&orig_graph);
	graph_delete(&longest_path_graph);
}