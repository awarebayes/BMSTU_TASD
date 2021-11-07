//
// Created by dev on 11/7/21.
//

#include "menu.h"
#include "util.h"
#include "queue.h"
#include "solution.h"
#include "memory.h"

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

void main_loop()
{
	int choice = 0;
	char *choices[] = {
			"[Simulate] - List Queue",
			"[Simulate] - Vector Queue",
			"[Debug]    - Show fragmentation"
	};

	simulation_times_t times = {
			.await = { .low = 0, .high = 5 },
			.work_1 = { .low = 0, .high = 4 },
			.work_2 = { .low = 0, .high = 4 },
	};

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
		}
	}
}