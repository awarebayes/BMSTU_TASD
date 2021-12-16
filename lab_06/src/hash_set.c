//
// Created by dev on 11/30/21.
//

#include "hash_set.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 512
#define RAND_STR_BUF_SIZE 16

node *node_new(const char *value)
{
	node *self = xmalloc(sizeof(node));
	self->data = xmalloc(sizeof(char) * (strlen(value) + 1));
	strcpy(self->data, value);
	return self;
}

void node_delete(node *self)
{
	free(self->data);
	free(self);
}

void node_delete_recursive(node *self)
{
	if (self == NULL)
		return;
	node_delete_recursive(self->next);
	free(self->data);
	free(self);
}

hash_set hash_set_new(size_t capacity, int (*hash_func) (void *arg))
{
	hash_set self = { 0 };
	self.size = 0;
	self.capacity = capacity;
	self.hash_func = hash_func;
	self.nodes = (node **)xmalloc(sizeof(node) * capacity);
	return self;
}

void hash_set_delete(hash_set *self)
{
	for (size_t i = 0; i < self->capacity; i++)
	{
		node *node = self->nodes[i];
		node_delete_recursive(node);
	}
	free(self->nodes);
	self->nodes = 0;
}

int hash_set_add(hash_set *self, char *key)
{
	int hash = self->hash_func(key) % self->capacity;
	node *to_add = node_new(key);
	int n_comparisons = 0;

	node *starting_node = self->nodes[hash];
	if (starting_node == NULL)
		self->nodes[hash] = to_add;
	else
	{
		while (starting_node->next != NULL)
		{
			starting_node = starting_node->next;
			n_comparisons++;
		}
		starting_node->next = to_add;
	}
	self->size++;
	return n_comparisons;
}

node *hash_set_search(hash_set *self, char *key)
{
	int hash = self->hash_func(key) % self->capacity;
	node *current = self->nodes[hash];
	while (current != NULL)
	{
		if (strcmp(current->data, key) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

node *hash_set_search_cmp_log(hash_set *self, char *key, int *cmp)
{
	int hash = self->hash_func(key) % self->capacity;
	node *current = self->nodes[hash];
	while (current != NULL)
	{
		(*cmp)++;
		if (strcmp(current->data, key) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

node *hash_set_remove(hash_set *self, char *key)
{
	int hash = self->hash_func(key) % self->capacity;
	node *current = self->nodes[hash];
	node *prev = NULL;
	while (current != NULL)
	{
		if (strcmp(current->data, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				self->nodes[hash] = NULL;
			current->next = NULL;
			return current;
		}
		prev = current;
		current = current->next;
	}
	return NULL;
}

void hash_set_print(hash_set *self)
{
	for (size_t i = 0; i < self->capacity; i++)
	{
		node *current = self->nodes[i];
		printf("[index: %2zu] ", i);
		while (current != NULL)
		{
			printf("%s -> ", current->data);
			current = current->next;
		}
		printf("null\n");
	}
}


hash_set hash_set_read(char *cwd, char *file_name_no_ext, size_t capacity, hash_func_t hash_func, int *ec)
{
	int local_ec = 0;
	char buf[BUF_SIZE] = { 0 };
	snprintf(buf, BUF_SIZE, "%s%s", cwd, file_name_no_ext);
	FILE *f = fopen(buf, "r");
	if (!f)
		local_ec = input_err;
	hash_set self = hash_set_new(capacity, hash_func);
	char temp[BUF_SIZE];
	while (!feof(f) && !local_ec)
	{
		if (fscanf(f, "%s", temp) != 1)
			local_ec = input_err;
		hash_set_add(&self, temp);
	}
	fclose(f);
	if (ec)
		*ec = local_ec;
	return self;
}

hash_set hash_set_random(int size, int capacity, char *random_word)
{
	int added = 0;
	hash_set hset = hash_set_new(capacity, sdbm);
	int random_word_idx = rand() % size;

	char buf[RAND_STR_BUF_SIZE];
	while (added < size)
	{
		rand_string(buf, RAND_STR_BUF_SIZE);
		if (hash_set_search(&hset, buf) == NULL)
		{
			if (random_word_idx == added)
				strcpy(random_word, buf);
			hash_set_add(&hset, buf);
			added++;
		}
	}
	return hset;
}
