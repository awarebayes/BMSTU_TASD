
// Created by dev on 11/25/21.
//

#ifndef LAB_06_B_TREE_H
#define LAB_06_B_TREE_H

#include "b_node.h"
#include <stdio.h>

// @constructor
// tree is constructed with b_node_new()
// @destructor
void b_tree_delete(struct b_node *self);

struct b_node *b_tree_insert(struct b_node *self, struct b_node *node);

void b_tree_to_dot(char *path, char *tree_name, struct b_node *self);

struct b_node* b_tree_read(char *cwd, char *tree_name);

struct b_node *b_tree_remove(struct b_node *self, char *key);

int b_tree_assert_valid(struct b_node *self);

void b_tree_to_dot_cwd(char *cwd, char *path, char *tree_name, struct b_node *self);

#endif //LAB_06_B_TREE_H
