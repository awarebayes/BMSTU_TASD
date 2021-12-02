//
// Created by dev on 11/25/21.
//


#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "avl_node.h"
#include "util.h"

#define BUF_SIZE 2048
#define RAND_STR_BUF_SIZE 128


void avl_tree_delete(struct avl_node *self)
{
	// post order traversal with deletion
	if (self == NULL)
		return;

	if (self->left != NULL || self->right != NULL)
	{
		avl_tree_delete(self->left);
		avl_tree_delete(self->right);
	}
	avl_node_delete(self);
}

int avl_tree_height(struct avl_node *self)
{
	if (self == NULL)
		return 0;
	return self->height;
}

static int max(int a, int b)
{
	return (a > b) ? a : b;
}

struct avl_node *avl_tree_rotate_right(struct avl_node *y)
{
	struct avl_node *x = y->left;
	struct avl_node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(avl_tree_height(y->left), avl_tree_height(y->right)) + 1;
	x->height = max(avl_tree_height(x->left), avl_tree_height(x->right)) + 1;

	return x;
}

struct avl_node *avl_tree_rotate_left(struct avl_node *x)
{
	struct avl_node *y = x->right;
	struct avl_node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(avl_tree_height(x->left), avl_tree_height(x->right)) + 1;
	y->height = max(avl_tree_height(y->left), avl_tree_height(y->right)) + 1;

	return y;
}

int avl_tree_get_balance(struct avl_node *self)
{
	if (self == NULL)
		return 0;
	return avl_tree_height(self->left) - avl_tree_height(self->right);
}

struct avl_node *avl_tree_rebalance(struct avl_node *self, char *key)
{
	self->height = 1 + max(avl_tree_height(self->left), avl_tree_height(self->right));
	int balance = avl_tree_get_balance(self);

	// Left Left Case
	if (balance > 1 && strcmp(key, self->left->data) < 0)
		return avl_tree_rotate_right(self);

	// Right Right Case
	if (balance < -1 && strcmp(key, self->right->data) > 0)
		return avl_tree_rotate_left(self);

	// Left Right Case
	if (balance > 1 && strcmp(key, self->left->data) > 0)
	{
		self->left = avl_tree_rotate_left(self->left);
		return avl_tree_rotate_right(self);
	}

	// Right Left Case
	if (balance < -1 && strcmp(key, self->right->data) < 0)
	{
		self->right = avl_tree_rotate_right(self->right);
		return avl_tree_rotate_left(self);
	}

	return self;
}

struct avl_node *avl_tree_insert(struct avl_node *self, struct avl_node *node)
{
	if (self == NULL)
		return node;

	int cmp = strcmp(self->data, node->data);
	if (cmp == 0)
	{
		printf("Tree cannot have two similar keys, exiting...\n");
		exit(EXIT_FAILURE);
	}
	else if (cmp > 0)
		self->left = avl_tree_insert(self->left, node);
	else
		self->right = avl_tree_insert(self->right, node);

	self = avl_tree_rebalance(self, node->data);

	return self;
}


struct avl_node *avl_tree_add(struct avl_node *self, char *key)
{

	struct avl_node *node = avl_node_new(key);
	return avl_tree_insert(self, node);
}

struct avl_node *avl_tree_min_value(struct avl_node *self)
{
	struct avl_node *temp = self;
	while (temp->left != NULL)
		temp = temp->left;
	return temp;
}


int avl_tree_assert_valid(struct avl_node *self)
{
	if (self == NULL)
		return 1;

	assert(avl_tree_get_balance(self) <= 1);
	assert(avl_tree_get_balance(self) >= -1);

	if (self->left != NULL)
	{
		assert(strcmp(self->left->data, self->data) < 0);
		assert(avl_tree_assert_valid(self->left));
	}

	if (self->right != NULL)
	{
		assert(strcmp(self->right->data, self->data) > 0);
		assert(avl_tree_assert_valid(self->right));
	}
	return 1;
}


struct avl_node *avl_tree_remove(struct avl_node *self, char *key)
{
	if (self == NULL)
		return NULL;

	if (strcmp(key, self->data) < 0)
		self->left = avl_tree_remove(self->left, key);

	else if (strcmp(key, self->data) > 0)
		self->right = avl_tree_remove(self->right, key);

	else
	{
		if ( (self->left == NULL) || (self->right == NULL))
		{
			struct avl_node *temp = self->left ? self->left : self->right;
			// no children
			if (temp == NULL)
			{
				temp = self;
				self = NULL;
			}
				// one child
			else
				*self = *avl_node_deep_copy(temp);
			avl_node_delete(temp);
		}
		else
		{
			struct avl_node *temp = avl_tree_min_value(self->right);
			free(self->data);
			self->data = xmalloc(sizeof(char) * strlen(temp->data) + 1);
			strcpy(self->data, temp->data);
			self->right = avl_tree_remove(self->right, temp->data);
		}
	}

	if (self == NULL)
		return self;

	self->height = 1 + max(avl_tree_height(self->left), avl_tree_height(self->right));
	int balance = avl_tree_get_balance(self);

	// LL case
	if (balance > 1 && avl_tree_get_balance(self->left) >= 0)
		return avl_tree_rotate_right(self);

	// LR case
	if (balance > 1 && avl_tree_get_balance(self->left) < 0)
	{
		self->left = avl_tree_rotate_left(self->left);
		return avl_tree_rotate_right(self);
	}

	// RR
	if (balance < -1 && avl_tree_get_balance(self->right) <= 0)
		return avl_tree_rotate_left(self);

	// RL
	if (balance < -1 && avl_tree_get_balance(self->right) > 0)
	{
		self->right = avl_tree_rotate_right(self->right);
		return avl_tree_rotate_left(self);
	}

	return self;
}

struct avl_node *avl_tree_search(struct avl_node *self, const char *data)
{
	if (self == NULL)
		return NULL;

	int cmp = strcmp(self->data, data);
	if (cmp == 0)
		return self;
	else if (cmp > 0)
		return avl_tree_search(self->left, data);
	else
		return avl_tree_search(self->right, data);
}

void avl_tree_apply_preorder(struct avl_node *self, void (*f)(struct avl_node *, void *), void *arg)
{
	if (self == NULL)
		return;
	f(self, arg);
	avl_tree_apply_preorder(self->left, f, arg);
	avl_tree_apply_preorder(self->right, f, arg);
}

struct avl_node *avl_tree_read(char *cwd, char *file_name_no_ext, int *ec)
{
	int local_ec = 0;
	char buf[BUF_SIZE] = { 0 };
	snprintf(buf, BUF_SIZE, "%s%s", cwd, file_name_no_ext);
	FILE *f = fopen(buf, "r");
	if (!f)
		local_ec = input_err;
	struct avl_node *self = NULL;
	char temp[BUF_SIZE];
	while (!feof(f) && !local_ec)
	{
		if (fscanf(f, "%s", temp) != 1)
			local_ec = input_err;
		struct avl_node *node = avl_node_new(temp);
		self = avl_tree_insert(self, node);
	}
	fclose(f);
	if (ec)
		*ec = local_ec;
	return self;
}

int avl_tree_n_nodes(struct avl_node *self)
{
	if (self == NULL)
		return 0;

	int acc = 1;
	if (self->left != NULL)
		acc += avl_tree_n_nodes(self->left);
	if (self->right != NULL)
		acc += avl_tree_n_nodes(self->right);
	return acc;
}

struct avl_node *avl_tree_random(int size, char *random_word)
{
	int added = 0;
	int random_word_index = rand() % size;
	struct avl_node *tree = NULL;

	char buf[RAND_STR_BUF_SIZE];
	while (added < size)
	{
		rand_string(buf, RAND_STR_BUF_SIZE);
		if (avl_tree_search(tree, buf) == NULL)
		{
			if (random_word_index == added)
				strcpy(random_word, buf);
			tree = avl_tree_add(tree, buf);
			added++;
		}
	}
	return tree;
}

