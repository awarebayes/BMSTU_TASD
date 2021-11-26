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
		assert(0);
	else if (cmp > 0)
		self->left = avl_tree_insert(self->left, node);
	else
		self->right = avl_tree_insert(self->right, node);

	self = avl_tree_rebalance(self, node->data);

	return self;
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
	assert(avl_tree_get_balance(self) >=-1);

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

	if (strcmp(key, self->data) > 0)
		self->right = avl_tree_remove(self->right, key);

	else
	{
		if (self->left == NULL)
		{
			struct avl_node *temp = self->right;
			avl_node_delete(self);
			return temp;
		}
		else if (self->right == NULL)
		{
			struct avl_node *temp = self->left;
			avl_node_delete(self);
			return temp;
		}
		// get minimum node
		struct avl_node *temp = avl_tree_min_value(self->right);

		free(self->data);
		size_t new_len = strlen(temp->data) + 1;
		self->data = xmalloc(new_len);
		strncpy(self->data, temp->data, new_len);

		self->right = avl_tree_remove(self->right, temp->data);
	}

	self->height = 1 + max(avl_tree_height(self->left), avl_tree_height(self->right));
	int balance = avl_tree_get_balance(self);

	if (balance > 1 && avl_tree_get_balance(self->left) >= 0)
		return avl_tree_rotate_right(self);

	if (balance > 1 && avl_tree_get_balance(self->left) < 0)
	{
		self->left = avl_tree_rotate_left(self->left);
		return avl_tree_rotate_right(self);
	}

	if (balance < -1 && avl_tree_get_balance(self->right) <= 0)
		return avl_tree_rotate_left(self);

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
	else if (cmp < 0)
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

static void to_dot(struct avl_node *self, void *param)
{
	FILE *f = param;
	if (self->left)
		fprintf(f, "%s -> %s;\n", self->data, self->left->data);

	if (self->right)
		fprintf(f, "%s -> %s;\n", self->data, self->right->data);
}

void avl_tree_to_dot(char *cwd, char *tree_name, struct avl_node *self)
{
	char buf[BUF_SIZE] = { 0 };
	snprintf(buf, BUF_SIZE, "%s%s.dot", cwd, tree_name);
	FILE *f = fopen(buf, "w");
	fprintf(f, "digraph %s {\n", tree_name);

	avl_tree_apply_preorder(self, to_dot, f);

	fprintf(f, "}\n");
	fclose(f);
}

struct avl_node *avl_tree_read(char *cwd, char *tree_name)
{
	char buf[BUF_SIZE] = { 0 };
	snprintf(buf, BUF_SIZE, "%s%s.txt", cwd, tree_name);
	FILE *f = fopen(buf, "r");
	struct avl_node *self = NULL;
	char temp[BUF_SIZE];
	while (!feof(f))
	{
		fscanf(f, "%s", temp);
		struct avl_node *node = avl_node_new(temp);
		self = avl_tree_insert(self, node);
	}
	fclose(f);
	return self;
}

