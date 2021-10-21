//
// Created by dev on 10/21/21.
//

#include "tests.h"
#include <assert.h>
#include "stack.h"
#include "list.h"
#include "solution.h"

void check_stack()
{
	stack_t stack = stack_new(10);
	assert(stack_size(&stack) == 10);
	assert(stack.ps == stack.arr - 1);

	stack_push(&stack, 1);

	assert(stack.ps == stack.arr);
	assert(*stack.ps == 1);
	assert(stack_pop(&stack) == 1);
	assert(stack_empty(&stack));

	for (int i = 0; i < 10; i++)
		stack_push(&stack, i);

	assert(!stack_empty(&stack));
	assert(*stack.ps == 9);

	stack_push(&stack, 10);
	stack_push(&stack, 11);

	assert(stack_size(&stack) == 20);
	assert(*stack.ps == 11);
	stack_delete(&stack);
}

void check_list()
{
	list_t list = list_new();
	assert(list.first == list.last);

	list_add(&list, 1);

	assert(list.first->value == 1);
	assert(list.first == list.last);
	assert(list.first->next == NULL);
	assert(list.first->prev == NULL);

	list_add(&list, 2);

	assert(list.first->value == 1);
	assert(list.first->next == list.last);
	assert(list.last->prev == list.first);
	assert(list.last->next == NULL);
	assert(list.first->prev == NULL);

	assert(list_pop(&list) == 2);

	assert(list.first->value == 1);
	assert(list.first == list.last);
	assert(list.first->next == NULL);
	assert(list.first->prev == NULL);

	for (int i = 2; i < 10; i++)
	{
		list_add(&list, i);
		assert(list.last->value == i);
	}

	for (int i = 9; i >= 2; i--)
	{
		assert(list.last->next == NULL);
		assert(list.last->prev->value == i - 1);
		assert(list.last->value == i);
		assert(list_pop(&list) == i);
	}
	list_pop(&list);
	assert(list_empty(&list));
	list_delete(&list);
}

void check_solution_stack()
{
	assert(is_palindrome_stack("") == 1);
	assert(is_palindrome_stack("a") == 1);
	assert(is_palindrome_stack("ab") == 0);
	assert(is_palindrome_stack("aba") == 1);
	assert(is_palindrome_stack("abac") == 0);
	assert(is_palindrome_stack("acaca") == 1);
	assert(is_palindrome_stack("acbca") == 1);
	assert(is_palindrome_stack("abracadabra") == 0);
}

void check_solution_list()
{
	assert(is_palindrome_list("") == 1);
	assert(is_palindrome_list("a") == 1);
	assert(is_palindrome_list("ab") == 0);
	assert(is_palindrome_list("aba") == 1);
	assert(is_palindrome_list("abac") == 0);
	assert(is_palindrome_list("acaca") == 1);
	assert(is_palindrome_list("acbca") == 1);
	assert(is_palindrome_list("abracadabra") == 0);
}

void check_all()
{
	check_stack();
	check_list();
	check_solution_stack();
	check_solution_list();
}