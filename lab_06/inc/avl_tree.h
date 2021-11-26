//
// Created by dev on 11/25/21.
//

#ifndef LAB_06_AVL_TREE_H
#define LAB_06_AVL_TREE_H

#include "avl_node.h"
#include <stdio.h>

// @constructor
// tree is constructed with b_node_new()
// @destructor
void avl_tree_delete(struct avl_node *self);

struct avl_node *avl_tree_insert(struct avl_node *self, struct avl_node *node);

void avl_tree_to_dot(char *path, char *tree_name, struct avl_node *self);

struct avl_node* avl_tree_read(char *cwd, char *tree_name);

void avl_tree_to_dot_cwd(char *cwd, char *path, char *tree_name, struct avl_node *self);

struct avl_node *avl_tree_remove(struct avl_node *self, char *key);

int avl_tree_assert_valid(struct avl_node *self);

#endif //LAB_06_AVL_TREE_H
