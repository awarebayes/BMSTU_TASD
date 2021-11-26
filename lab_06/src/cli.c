//
// Created by dev on 11/25/21.
//

#include "b_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define BUF_SIZE 512

int run_dot(char *cwd, char *tree_name)
{
	char command_string[BUF_SIZE] = { 0 };

	snprintf(command_string, BUF_SIZE, "dot -Tpng %s%s.dot > %s%s.png",
	         cwd,
	         tree_name,
	         cwd,
	         tree_name);
	return system(command_string);
}
