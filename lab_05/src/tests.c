//
// Created by dev on 10/21/21.
//

#include "tests.h"
#include <assert.h>
#include "queue_list.h"
#include "queue_vec.h"

void check_list_queue()
{

	queue_list_t q = queue_list_new(sizeof(int), 100);
	int pop_res = 0;

	assert(queue_list_empty(&q));
	int one = 1;
	queue_list_add(&q, &one);
	queue_list_pop(&q, &pop_res);
	assert(pop_res == one);
	assert(queue_list_empty(&q));

	for (int i = 0; i < 10; i++)
	{
		queue_list_add(&q, &i);
	}

	for (int i = 0; i < 10; i++)
	{
		queue_list_pop(&q, &pop_res);
		assert(pop_res == i);
	}
	assert(queue_list_empty(&q));

	for (int i = 0; i < 10; i++)
		queue_list_insert_front(&q, &i, 0);

	for (int i = 0; i < 10; i++)
	{
		queue_list_pop(&q, &pop_res);
		assert(pop_res == 9 - i);
	}
	assert(queue_list_empty(&q));

	for (int i = 0; i < 10; i++)
		queue_list_add(&q, &i);
	int ott = 123;
	queue_list_insert_front(&q, &ott, 1);
	queue_list_pop(&q, &pop_res);
	assert(pop_res == 0);

	queue_list_pop(&q, &pop_res);
	assert(pop_res == ott);

	for (int i = 1; i < 10; i++)
	{
		queue_list_pop(&q, &pop_res);
		assert(pop_res == i);
	}
	assert(queue_list_empty(&q));

	queue_list_delete(&q);
}


void check_vec_queue()
{

	queue_vec_t q = queue_vec_new(sizeof(int), 20);
	int pop_res = 0;

	assert(queue_vec_empty(&q));
	int one = 1;
	queue_vec_add(&q, &one);
	queue_vec_pop(&q, &pop_res);
	assert(pop_res == one);
	assert(queue_vec_empty(&q));


	for (int i = 1; i < 21; i++)
	{
		for (int j = 0; j < i; j++)
			queue_vec_add(&q, &j);
		for (int j = 0; j < i; j++)
		{
			queue_vec_pop(&q, &pop_res);
			assert(pop_res == j);
		}
		assert(queue_vec_empty(&q));
	}


	assert(queue_vec_empty(&q));
	for (int j = 0; j < 20; j++)
		queue_vec_add(&q, &j);

	assert(queue_vec_full(&q));
	queue_vec_pop(&q, &pop_res);
	assert(pop_res == 0);
	assert(!queue_vec_full(&q));
	for (int j = 1; j < 20; j++)
	{
		queue_vec_pop(&q, &pop_res);
		assert(pop_res == j);
	}
	assert(queue_vec_empty(&q));

	for (int c = 0; c < 10; c++)
	{
		for (int i = 0; i < 10; i++)
			queue_vec_add(&q, &i);

		int ott = 123;
		queue_vec_insert_swap_front(&q, &ott, 4);

		queue_vec_pop(&q, &pop_res);
		assert(pop_res == 3); // 0 1 2 3 <-

		for (int i = 0; i < 3; i++)
		{
			queue_vec_pop(&q, &pop_res);
			assert(pop_res == i);
		}

		queue_vec_pop(&q, &pop_res);
		assert(pop_res == ott); // 0 1 2 3

		for (int i = 4; i < 10; i++)
		{
			queue_vec_pop(&q, &pop_res);
			assert(pop_res == i);
		}

		assert(queue_vec_empty(&q));
	}
	queue_vec_delete(&q);
}

void check_all()
{
	check_list_queue();
	check_vec_queue();
}
