#include "menu.h"
#include "util.h"
#include "stack.h"
#include "list.h"
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#define EXIT_CHOICE 123
#define TIMES 50

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

void solve_ask()
{
	char strbuf[BUFFER_SIZE];
	int ec = 0;
	do
		read_str(stdin, stdout, "Input a string: ", strbuf, &ec);
	while (ec != 0);
	int choice = -1;
	int solution = -1;
	while (choice < 1 && !ec)
	{
		ec = 0;
		printf("Solving palindrome using\n1 - Array\n2 - List\n");
		read_int(stdin, stdout, "Choice: ", &choice, &ec);
		if (choice != 1 && choice != 2)
			choice = -1;
	}
	if (choice == 1)
		solution = is_palindrome_list(strbuf);
	else
		solution = is_palindrome_stack(strbuf);
	if (solution)
		printf("String is a palindrome! Grace and rejoice!\n");
	else
		printf("Not a palindrome! :( \n");
}

void menu_speed_profile()
{
	printf("Speed profile:\n");
	int sizes[] = { 10, 50, 100, 500, 1000, 5000, 10000 };
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	uint64_t start, end;
	printf("|%16s|%33s|%33s|\n", "", "random", "palindrome");
	printf("|%16s|%16s|%16s|%16s|%16s|\n", "size", "stack", "list", "stack", "list");
	uint64_t mean = 0;
	for (int i = 0; i < n_sizes; i++)
	{
		int size = sizes[i];

		char *string = rand_string(size);
		char *palindrome = rand_palindrome(size);
		printf("|%16d|", size);

		// string
		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			start = clock();
			is_palindrome_stack(string);
			end = clock();
			mean += end - start;
		}
		printf("%16lu|", mean / TIMES);

		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			start = clock();
			is_palindrome_list(string);
			end = clock();
			mean += end - start;
		}
		printf("%16lu|", mean / TIMES);

		// string
		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			start = clock();
			is_palindrome_stack(palindrome);
			end = clock();
			mean += end - start;
		}
		printf("%16lu|", mean / TIMES);

		mean = 0;
		for (int j = 0; j < TIMES; j++)
		{
			start = clock();
			is_palindrome_list(palindrome);
			end = clock();
			mean += end - start;
		}
		printf("%16lu|\n", mean / TIMES);

		free(string);
		free(palindrome);
	}
}


void menu_memory_profile()
{
	printf("Memory profile:\n");
	size_t sizes[] = { 10, 100, 1000, 10000, 100000 };
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	printf("|%16s|%33s|%33s|\n", "size", "stack", "list");
	for (int i = 0; i < n_sizes; i++)
	{
		size_t size = sizes[i];

		char *string = rand_string(size);
		char *palindrome = rand_palindrome(size);
		printf("|%16ld|", size);
		printf("|%32ld|", stack_memsize_theoretic(size));
		printf("|%32ld|\n", list_memsize_theoretic(size));

		free(string);
		free(palindrome);
	}
}

void main_loop()
{
	int choice = 0;
	char *choices[] = {
			"[Array stack] - Add",
			"[Array stack] - Pop",
			"[Array stack] - Print",
			"[Array stack] - Memory usage",
			"[List  stack] - Add",
			"[List  stack] - Pop",
			"[List  stack] - Print",
			"[List  stack] - Memory usage",
			"[Task]        - Is string palindrome",
			"[Debug]       - Delted memory addresses",
			"[Misc]       - Profile speed",
			"[Misc]       - Profile memory"
	};

	stack_t stack = stack_new(10);
	list_t list = list_new();

	int i = 0;
	int ec = 0;
	while (choice != EXIT_CHOICE)
	{
		ec = 0;
		printf("\n");
		choice = get_choice(sizeof(choices) / sizeof(char *), choices);
		printf("\n");
		switch (choice)
		{
			case 0:
				i = 0;
				read_int(stdin, stdout, "Input integer: ", &i, &ec);
				if (!ec)
					stack_push(&stack, i);
				else
					printf("There was an error in Your input:\n");
				break;
			case 1:
				if (stack_empty(&stack))
					printf("Cannot pop from an empty stack!\n");
				else
					printf("Popped: %d\n", stack_pop(&stack));
				break;
			case 2:
				stack_print(&stack);
				break;
			case 3:
				printf("Array stack uses %ld bytes\n", stack_memsize(&stack));
				break;
			case 4:
				i = 0;
				read_int(stdin, stdout, "Input integer: ", &i, &ec);
				if (!ec)
					list_add(&list, i);
				break;
			case 5:
				if (list_empty(&list))
					printf("Cannot pop from an empty stack!\n");
				else
					printf("Popped: %d\n", list_pop(&list));
				break;
			case 6:
				list_print(&list);
				break;
			case 7:
				printf("List stack uses %ld bytes\n", sizeof(list) + cons_memsize(list.top));
				break;
			case 8:
				solve_ask();
				break;
			case 9:
				log_print_deleted_addresses();
				break;
			case 10:
				menu_speed_profile();
				break;
			case 11:
				menu_memory_profile();
				break;
			default:
				break;
		}
	}

	stack_delete(&stack);
	list_delete(&list);
}