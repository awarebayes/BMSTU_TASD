
// Created by dev on 11/25/21.
//

#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>
#include "b_tree.h"

#define BUF_SIZE 2048


void b_tree_delete(struct b_node *self)
{
	// post order traversal with deletion
	if (self == NULL)
		return;

	if (self->left != NULL || self->right != NULL)
	{
		b_tree_delete((struct b_node *) self->left);
		b_tree_delete((struct b_node *) self->right);
	}
	b_node_delete(self);
}

struct b_node *b_tree_insert(struct b_node *self, struct b_node *node)
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
		self->left = b_tree_insert(self->left, node);
	else
		self->right = b_tree_insert(self->right, node);
	return self;
}

struct b_node *b_tree_search(struct b_node *self, const char *data)
{
	if (self == NULL)
		return NULL;

	int cmp = strcmp(self->data, data);
	if (cmp == 0)
		return self;
	else if (cmp > 0)
		return b_tree_search(self->left, data);
	else
		return b_tree_search(self->right, data);
}

struct b_node *b_tree_min_value(struct b_node *self)
{
	struct b_node *current = self;
	while (current && current->left != NULL)
		current = current->left;
	return current;
}

int b_tree_assert_valid(struct b_node *self)
{
	if (self == NULL)
		return 1;

	if (self->left != NULL)
	{
		assert(strcmp(self->left->data, self->data) < 0);
		assert(b_tree_assert_valid(self->left));
	}

	if (self->right != NULL)
	{
		assert(strcmp(self->right->data, self->data) > 0);
		assert(b_tree_assert_valid(self->right));
	}
	return 1;
}

struct b_node *b_tree_remove(struct b_node *self, char *key)
{
	if (self == NULL)
		return NULL;
	if (strcmp(self->data, key) > 0)
		self->left = b_tree_remove(self->left, key);
	else if (strcmp(self->data, key) < 0)
		self->right = b_tree_remove(self->right, key);
	else
	{
		if (self->left == NULL)
		{
			struct b_node *temp = self->right;
			b_node_delete(self);
			return temp;
		}
		else if (self->right == NULL)
		{
			struct b_node *temp = self->left;
			b_node_delete(self);
			return temp;
		}
		// get minimum node
		struct b_node *temp = b_tree_min_value(self->right);

		free(self->data);
		self->data = xmalloc(strlen(temp->data) + 1);
		strcpy(self->data, temp->data);

		self->right = b_tree_remove(self->right, temp->data);
	}

	return self;
}

void b_tree_apply_preorder(struct b_node *self, void (*f)(struct b_node *, void *), void *arg)
{
	if (self == NULL)
		return;
	f(self, arg);
	b_tree_apply_preorder(self->left, f, arg);
	b_tree_apply_preorder(self->right, f, arg);
}

struct b_node *b_tree_read(char *cwd, char *file_name_no_ext, int *ec)
{
	int local_ec = 0;
	char buf[BUF_SIZE] = { 0 };
	snprintf(buf, BUF_SIZE, "%s%s", cwd, file_name_no_ext);
	FILE *f = fopen(buf, "r");
	if (!f)
		local_ec = input_err;
	struct b_node *self = NULL;
	char temp[BUF_SIZE];
	while (!feof(f) && !local_ec)
	{
		if (fscanf(f, "%s", temp) != 1)
			local_ec = input_err;
		struct b_node *node = b_node_new(temp);
		self = b_tree_insert(self, node);
	}
	if (ec != NULL)
		*ec = local_ec;
	if (f)
		fclose(f);
	return self;
}


