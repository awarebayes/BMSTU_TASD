//
// Created by dev on 11/5/21.
//

#include "queue.h"
#include "task.h"
#include "util.h"
#include "solution.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>


/*
void simulate(int queue_kind)
{
	queue_t queue = queue_new(queue_kind, sizeof(task_t), 20);
	task_t task_2 = task_new(2);

	// times
	float in_low = 0.0f;
	float in_high = 5.0f;
	float out_low = 0.0f;
	float out_high = 4.0f;

	float time_in = 0;
	float time_out = -1;
	float hold_time = 0;
	float service_time = 0;

	int tasks_in = 1; // по заданию
	int tasks_out = 0;
	int tasks_out_1 = 0;
	int tasks_failed = 0;
	int calls = 0;
	int overall_len = 0;

	queue_add(&queue, &task_2);
	task_t todo_task = { 0 };

	while (tasks_out_1 != 1000)
	{

		if (time_out < 0 || time_in < time_out)
		{
			if (time_out < 0)
				hold_time += time_in;
			service_time += time_in;
			time_out -= time_in;
			time_in = rand_float(in_low, in_high);

			task_t task = task_new(1);
			if (!queue_full(&queue))
			{
				queue_add(&queue, &task);
				tasks_in += 1;
			}
			else
				tasks_failed += 1;
			if (time_out < 0 && !queue_empty(&queue))
			{
				queue_pop(&queue, &todo_task);
				time_out = rand_float(out_low, out_high);
			}
		}
		else
		{
			// work
			time_in -= time_out;
			service_time += time_out;
			time_out = 0;
			calls += 1;
			overall_len += queue_size(&queue);
			tasks_out += 1;
			if (todo_task.type == 2)
			{
				if (!queue_full(&queue))
					queue_insert_front(&queue, &todo_task, 4);
				else
				{
					printf("Queue is full, cannot add task #2");
					exit(1);
				}
			}
			else
			{
				tasks_out_1 += 1;
				if (tasks_out % 100 == 0)
				{
					printf(
							"---"
							"Processed %d tasks\n"
							"Queue size: %zu\n"
							"Mean queue size: %u\n",
							tasks_out,
							queue_size(&queue),
							overall_len / tasks_out
					);
				}
			}

			todo_task.type = 0;

			if (queue_empty(&queue))
				assert(0);
			else
			{
				queue_pop(&queue, &todo_task);
			 	time_out = rand_float(out_low, out_high);
			}
		}
	}

	float expected_time = 2500.0f;
	float err = fabsf(service_time - expected_time) / expected_time * 100;

	printf("----\n"
			"[Service time %f, (expected: %f, err: %.2f %% )]\n"
			"Tasks in: %d\n"
			"Tasks out: %d\n"
			"Tasks failed: %d\n"
			"Calls: %d\n"
			"Stall: %f\n",
			service_time,
			expected_time,
			err,
			tasks_in,
			tasks_out,
			tasks_failed,
			calls,
			hold_time
		   );
}
 */

float await(timespan_t time)
{
	return rand_float(time.low, time.high);
}

float work(timespan_t time)
{
	return rand_float(time.low, time.high);
}

void simulate(simulation_times_t times, int queue_kind)
{
	float fetch_time = 0;
	float work_time = 0;
	float global_time = 0;

	float time_to_fetch = 0;
	float time_to_work = 0;

	size_t capacity = 20;

	queue_t queue = queue_new(queue_kind, sizeof(task_t), capacity);
	sim_log_t log = { .tasks_in = 1 };

	task_t task_2 = task_new(2);
	queue_add(&queue, &task_2);

	while (log.tasks_out != 1000)
	{
		// There will always be a second type task_to_process in the queue
		// but better assert
		assert(!queue_empty(&queue));

		// time to fetch a new task
		if (time_to_fetch == 0)
		{
			time_to_fetch = await(times.await);
			task_t new_task = task_new(1);
			if (queue_size(&queue) <= capacity - 1) // leave space for 2nd task
			{
				queue_add(&queue, &new_task);
				log.tasks_in += 1;
			}
			else
				log.tasks_failed += 1;
			fetch_time += time_to_fetch;
		}

		// time to process next
		if (time_to_work == 0)
		{
			task_t task_to_process = { 0 };
			queue_pop(&queue, &task_to_process);

			timespan_t work_timespan = task_to_process.type == 1 ? times.work_1 : times.work_2;
			time_to_work = work(work_timespan);

			work_time += time_to_work;
			log.calls += 1;
			log.tasks_out += 1;

			if (task_to_process.type == 1)
				log.tasks_out_1 += 1;
			else
				queue_insert_front(&queue, &task_to_process, 4);
		}

		float smallest_time = fminf(work_time, time_to_fetch);
		time_to_work -= smallest_time;
		time_to_fetch -= smallest_time;
	}

	float expected_time = 2500.0f;
	float err = fabsf(work_time - expected_time) / expected_time * 100;

	float hold_time = 0.0f;
	if (fetch_time > work_time)
		hold_time = fetch_time - work_time;

	printf("----\n"
	       "[Service time %f, (expected: %f, err: %.2f %% )]\n"
	       "Tasks in: %d\n"
	       "Tasks out: %d\n"
	       "Tasks failed: %d\n"
	       "Calls: %d\n"
	       "Hold time: %f\n",
	       work_time,
	       expected_time,
	       err,
	       log.tasks_in,
	       log.tasks_out,
	       log.tasks_failed,
	       log.calls,
	       hold_time
	);
}
