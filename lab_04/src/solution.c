//
// Created by dev on 10/21/21.
//
#include "solution.h"
#include "stack.h"
#include "list.h"
#include <string.h>

int is_palindrome_stack(const char *string)
{
	int len = strlen(string);
	int mid = len / 2;
	int flag = 1;
	stack_t stack = stack_new(mid + 1);
	int i = 0;
	for (i = 0; i < mid; i++)
	{
		stack_push(&stack, (int) string[i]);
	}
	if ((len % 2) == 1)
		i += 1; // ignore middle char

	for (; i < len && flag; i++)
	{
		if (stack_empty(&stack))
			flag = 0;
		else
		{
			int elem = stack_pop(&stack);
			if (elem != (int) string[i])
				flag = 0;
		}
	}
	stack_delete(&stack);
	return flag;
}

int is_palindrome_list(const char *string)
{
	int len = strlen(string);
	int mid = len / 2;
	int flag = 1;
	list_t stack = list_new();
	int i = 0;
	for (i = 0; i < mid; i++)
	{
		list_add(&stack, (int) string[i]);
	}
	if (len % 2 == 1)
		i += 1; // ignore middle char

	for (; i < len && flag; i++)
	{
		if (list_empty(&stack))
			flag = 0;
		else
		{
			int elem = list_pop(&stack);
			if (elem != (int) string[i])
				flag = 0;
		}
	}
	list_delete(&stack);
	return flag;
}
