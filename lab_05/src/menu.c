//
// Created by dev on 11/7/21.
//

#include "menu.h"
#include "util.h"
#include "queue.h"
#include "simulate_queue.h"
#include "memory.h"
#include "inttypes.h"

#define TIMES 50

const simulation_times_t default_times = {
		.fetch = { .low = 0, .high = 5 },
		.work_1 = { .low = 0, .high = 4 },
		.work_2 = { .low = 0, .high = 4 },
};


int get_choice(int argc, char **argv)
{
	int choice = -1;
	while (choice < 0)
	{
		int ec = 0;
		for (int i = 0; i < argc; i++)
		{
			printf("%d: %s\n", i, argv[i]);
		}
		printf("%d: EXIT\n", EXIT_CHOICE);
		read_int(stdin, stdout, "Your choice: ", &choice, &ec);
		if (ec)
		{
			choice = -1;
			continue;
		}
		if (choice < 0 || (choice > argc - 1 && choice != EXIT_CHOICE))
			choice = -1;
	}
	return choice;
}

simulation_times_t input_times(int *ec)
{
	simulation_times_t times = { 0 };
	if (!*ec)
		read_float(stdin, stdout, "times -> fetch -> low: ", &times.fetch.low, ec);
	if (!*ec)
		read_float(stdin, stdout, "times -> fetch -> high: ", &times.fetch.high, ec);
	if (!*ec)
		read_float(stdin, stdout, "times -> work_1 -> low: ", &times.work_1.low, ec);
	if (!*ec)
		read_float(stdin, stdout, "times -> work_1 -> high: ", &times.work_1.high, ec);
	if (!*ec)
		read_float(stdin, stdout, "times -> work_2 -> low: ", &times.work_2.low, ec);
	if (!*ec)
		read_float(stdin, stdout, "times -> work_2 -> high: ", &times.work_2.high, ec);
	return times;
}


void menu_speed_profile_pp()
{
	printf("Speed profile (push, pop):\n");
	int sizes[] = { 10, 50, 100, 500, 1000, 5000, 10000 };
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	uint64_t start, end;
	printf("|%16s|%33s|%33s|\n", "", "vec", "list");
	printf("|%16s|%16s|%16s|%16s|%16s|\n", "size", "add", "pop", "add", "pop");
	uint64_t mean = 0;
	uint64_t (*time_func)(void) = ticks;
	queue_list_t qlist = queue_list_new(sizeof(int), 10000);
	queue_vec_t qvec = queue_vec_new(sizeof(int), 10000);
	int pop_res = 0;
	for (int i = 0; i < n_sizes; i++)
	{
		int size = sizes[i];

		printf("|%16d|", size);

		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			start = time_func();
			for (int k = 0; k < sizes[i]; k++)
				queue_vec_add(&qvec, &j);
			end = time_func();
			mean += end - start;
		}
		printf("%16lu|", mean / TIMES);

		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			start = time_func();
			for (int k = 0; k < sizes[i]; k++)
				queue_vec_pop(&qvec, &pop_res);
			end = time_func();
			mean += end - start;
		}
		printf("%16lu|", mean / TIMES);

		for (int j = 0; j < TIMES; j++)
		{
			start = time_func();
			for (int k = 0; k < sizes[i]; k++)
				queue_list_add(&qlist, &j);
			end = time_func();
			mean += end - start;
		}
		printf("%16lu|", mean / TIMES);

		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			start = time_func();
			for (int k = 0; k < sizes[i]; k++)
				queue_list_pop(&qlist, &pop_res);
			end = time_func();
			mean += end - start;
		}
		printf("%16lu|\n", mean / TIMES);
	}
	queue_vec_delete(&qvec);
	queue_list_delete(&qlist);
}


void menu_memory_profile()
{
	printf("Memory profile (holding int):\n");
	size_t sizes[] = { 10, 100, 1000, 10000, 100000 };
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	printf("|%16s|%32s|%32s|\n", "size", "vec", "list");
	for (int i = 0; i < n_sizes; i++)
	{
		size_t size = sizes[i];

		printf("|%16ld", size);
		printf("|%32ld", queue_vec_memsize_theoretic(size, sizeof(int)));
		printf("|%32ld|\n", queue_list_memsize_theoretic(size, sizeof(int)));
	}
}


void menu_simulation_profile()
{
	printf("Running simulation...\n");


	uint64_t mean = 0;
	for (int j = 0; j < TIMES; j++)
	{
		mean += simulate_profile(default_times, queue_list_kind);
	}
	printf("List takes %lu on average\n", mean / TIMES);


	mean = 0;
	for (int j = 0; j < TIMES; j++)
	{
		mean += simulate_profile(default_times, queue_vec_kind);
	}
	printf("Vector takes %lu on average\n", mean / TIMES);

}

void main_loop()
{
	int choice = 0;
	char *choices[] = {
			"[Simulate] - List Queue",
			"[Simulate] - Vector Queue",
			"[Debug]    - Show fragmentation",
			"[Times]    - Change queue times",
			"[Profile]  - Profile pop/push operations",
			"[Profile]  - Profile memory",
			"[Profile]  - Profile simulation",
	};

	simulation_times_t times = default_times;

	int ec = 0;
	while (choice != EXIT_CHOICE)
	{
		printf("\n");
		choice = get_choice(sizeof(choices) / sizeof(char *), choices);
		printf("\n");
		switch (choice)
		{
			case 0:
				simulate(times, queue_list_kind);
				break;
			case 1:
				simulate(times, queue_vec_kind);
				break;
			case 2:
				log_print_deleted_addresses();
				break;
			case 3:
				ec = 0;
				simulation_times_t new_times = input_times(&ec);
				if (!ec)
					times = new_times;
				break;

			case 4:
				menu_speed_profile_pp();
				break;
			case 5:
				menu_memory_profile();
				break;
			case 6:
				menu_simulation_profile();
			default:
				break;
		}
	}
}

