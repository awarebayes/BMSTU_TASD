//
// Created by dev on 11/30/21.
//

#ifndef LAB_06_HASH_SET_H
#define LAB_06_HASH_SET_H

#include <stdio.h>

// Hashmap with open hashing using chained collision

struct node;
typedef struct node node;

typedef int (*hash_func_t) (void *arg);

struct node
{
	char *data;
	struct node *next;
};

typedef struct
{
	size_t size;
	size_t capacity;
	hash_func_t hash_func;
	node **nodes;
} hash_set;

node *node_new(const char *value);

void node_delete(node *self);

hash_set hash_set_new(size_t capacity, hash_func_t hash_func);

void hash_set_delete(hash_set *self);

// @returns: number of comparisons
int hash_set_add(hash_set *self, char *key);

node *hash_set_search(hash_set *self, char *key);

void hash_set_print(hash_set *self);

hash_set hash_set_read(char *cwd, char *file_name_no_ext, size_t capacity, hash_func_t hash_func, int *ec);

node *hash_set_remove(hash_set *self, char *key);

hash_set hash_set_random(int size, int capacity, char *random_word);

node *hash_set_search_cmp_log(hash_set *self, char *key, int *cmp);

#endif //LAB_06_HASH_SET_H
