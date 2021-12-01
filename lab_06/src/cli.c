//
// Created by dev on 11/25/21.
//

#include "b_tree.h"
#include "avl_tree.h"
#include "hash_set.h"
#include "util.h"
#include "graphviz.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#define BUF_SIZE 512
#define EXIT_CHOICE 123
#define TIMES 50

int run_dot(char *cwd, char *tree_name)
{
	char dot_command[BUF_SIZE] = { 0 };
	char open_command[BUF_SIZE] = { 0 };
	char filename[BUF_SIZE] = { 0 };
	snprintf(filename, BUF_SIZE, "%s%s", cwd, tree_name);
	snprintf(dot_command, BUF_SIZE, "dot -Tpng %s.dot > %s.png", filename, filename);
	snprintf(open_command, BUF_SIZE, "xdg-open %s.png", filename);
	int res = system(dot_command);
	// system(open_command);
	return res;
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

void profile_deletion(struct b_node *btree, struct avl_node *avl, hash_set hset)
{
	uint64_t (*time_func)(void) = ticks;
	uint64_t start = 0, end = 0;
	uint64_t mean = 0;
	char word_to_delete[BUF_SIZE] = { 0 };
	int ec = ok;

	printf("Starting to profile...\n");
	read_str(stdin, stdout, "Word to delete: ", word_to_delete, &ec);
	if (b_tree_search(btree, word_to_delete) == NULL)
	{
		printf("Word was not found!\n");
		return;
	}

	mean = 0;
	for (int j = 0; j < TIMES; j++)
	{
		start = time_func();
		btree = b_tree_remove(btree, word_to_delete);
		end = time_func();
		mean += end - start;
		struct b_node *node_new = b_node_new(word_to_delete);
		btree = b_tree_insert(btree, node_new);
	}

	printf("Mean binary tree deletion: %lu\n", mean / TIMES);

	int avl_nodes = avl_tree_n_nodes(avl);
	mean = 0;
	for (int j = 0; j < TIMES; j++)
	{
		start = time_func();
		avl = avl_tree_remove(avl, word_to_delete);
		end = time_func();
		mean += end - start;
		avl_tree_assert_valid(avl);
		int new_nodes = avl_tree_n_nodes(avl);
		assert(new_nodes == avl_nodes - 1);
		struct avl_node *node_new = avl_node_new(word_to_delete);
		avl = avl_tree_insert(avl, node_new);
		avl_tree_assert_valid(avl);
		assert(avl_tree_n_nodes(avl) == avl_nodes);
	}

	printf("Mean avl tree deletion: %lu\n", mean / TIMES);

	mean = 0;
	for (int j = 0; j < 1; j++)
	{
		start = time_func();
		node *word = hash_set_remove(&hset, word_to_delete);
		end = time_func();
		mean += end - start;
		node_delete(word);
		hash_set_insert(&hset, word_to_delete);
	}

	printf("Mean hash set deletion: %lu\n", mean / TIMES);
}


void memory_profile()
{
	printf("Memory profile:\n");
	size_t sizes[] = { 10, 100, 500, 1000, 5000, 10000 };
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	printf("|%16s|%32s|%32s|%32s|%32s|\n", "size", "btree", "avl", "hash_set (full, chains 100)",
	       "hash_set (full, chains 1000)");
	for (int i = 0; i < n_sizes; i++)
	{
		size_t size = sizes[i];
		size_t b_tree_size = sizeof(struct b_node) * size;
		size_t avl_tree_size = sizeof(struct avl_node) * size;
		size_t hash_set_size1 = sizeof(node) * size + sizeof(hash_set) + sizeof(node *) * 100;
		size_t hash_set_size2 = sizeof(node) * size + sizeof(hash_set) + sizeof(node *) * 1000;

		printf("|%16ld", size);
		printf("|%32ld", b_tree_size);
		printf("|%32ld", avl_tree_size);
		printf("|%32ld", hash_set_size1);
		printf("|%32ld|\n", hash_set_size2);

	}
}

static inline uint32_t mylog2(const uint32_t x)
{
	uint32_t y;
	__asm__ __volatile__ ( "\tbsr %1, %0\n"
	: "=r"(y)
	: "r" (x)
	);
	return y;
}

uint32_t max(uint32_t x, uint32_t y)
{
	if (x > y)
		return x;
	return y;
}

void profile_comparisons()
{

	printf("Memory profile:\n");
	uint32_t sizes[] = { 10, 100, 500, 1000, 5000, 10000};
	int n_sizes = sizeof(sizes) / sizeof(sizes[0]);
	printf("|%16s|%32s|%32s|%32s|%32s|\n", "size", "btree", "avl", "hash_set (full, chains 100)",
	       "hash_set (full, chains 1000)");
	for (int i = 0; i < n_sizes; i++)
	{
		uint32_t size = sizes[i];
		uint32_t b_tree_cmp = mylog2(size);
		uint32_t avl_tree_cmp = mylog2(size);
		uint32_t hash_set_cmp1 = size / 100;
		uint32_t hash_set_cmp2 = size / 1000;

		printf("|%16u", size);
		printf("|%32u", b_tree_cmp);
		printf("|%32u", avl_tree_cmp);
		printf("|%32u", hash_set_cmp1);
		printf("|%32u|\n", hash_set_cmp2);

	}
}

void main_loop()
{
	int choice = 0;
	char *choices[] = {
			"[Task]     - delete word",
			"[Task]     - visualize",
			"[HashSet]  - rebuild hash set",
			"[Profile]  - profile deletion (does not permanently delete word)",
			"[Profile]  - memory profile",
			"[Profile]  - average # comparisons",
	};

	size_t hash_set_size = 30;
	hash_func_t hash_funcs[] = { djb2, sdbm };
	int hash_func_idx = 1;

	int ec = 0;
	char *cwd = "./res/";
	char *btree_name = "btree";
	char *avl_name = "avl";
	char *input = "input.txt";
	char word_to_delete[BUF_SIZE] = { 0 };
	int show_null_children = 0;

	struct b_node *btree = b_tree_read(cwd, input, &ec);
	struct avl_node *avl = avl_tree_read(cwd, input, &ec);
	hash_set hset = hash_set_read(cwd, input, hash_set_size, hash_funcs[hash_func_idx], &ec);

	if (ec)
	{
		printf("Could not read structures, ensure %s/input.txt exists", cwd);
		exit(EXIT_FAILURE);
	}

	while (choice != EXIT_CHOICE)
	{
		ec = 0;
		printf("\n");
		choice = get_choice(sizeof(choices) / sizeof(char *), choices);
		printf("\n");
		switch (choice)
		{
			case 1:
				printf("Word to delete:\n");
				read_str(stdin, stdout, "", word_to_delete, &ec);
				if (b_tree_search(btree, word_to_delete) != NULL)
				{
					btree = b_tree_remove(btree, word_to_delete);
					avl = avl_tree_remove(avl, word_to_delete);
					node *word = hash_set_remove(&hset, word_to_delete);
					node_delete(word);
					printf("Word was successfully deleted!\n");
				}
				else
					printf("Word was not found!\n");
				break;
			case 2:
				read_int(stdin, stdout, "Show null children? (0/1): ", &show_null_children, &ec);
				graph_tree_to_dot(cwd, btree_name, btree, show_null_children);
				graph_tree_to_dot(cwd, avl_name, (struct b_node *) avl, show_null_children);
				if (run_dot(cwd, btree_name) != ok)
					printf("There was an error running dot...\n");
				if (run_dot(cwd, avl_name) != ok)
					printf("There was an error running dot...\n");
				if (!ec)
					printf("Look at trees in ./res/avl_1.png and ./res/btree.png\n");
				printf("Here is the hash set:\n");
				hash_set_print(&hset);
				break;
			case 3:
				read_int(stdin, stdout, "Input hast set size: ", (int *) &hash_set_size, &ec);
				read_int(stdin, stdout, "Choose hash function: (1 - djb2, 2 - sdbm): ", &hash_func_idx, &ec);
				hash_func_idx -= 1;
				if (hash_func_idx != 0 && hash_func_idx != 1)
				{
					printf("invalid hash function index, try again...\n");
					break;
				}
				hash_set_delete(&hset);
				hset = hash_set_read(cwd, input, hash_set_size, hash_funcs[hash_func_idx], &ec);
				break;

			case 4:
				profile_deletion(btree, avl, hset);
				break;
			case 5:
				memory_profile();
				break;
			case 6:
				profile_comparisons();
				break;
			default:
				break;
		}
	}
	hash_set_delete(&hset);
	avl_tree_delete(avl);
	b_tree_delete(btree);
}