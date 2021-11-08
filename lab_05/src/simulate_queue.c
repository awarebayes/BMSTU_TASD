//
// Created by dev on 11/5/21.
//

#include "queue.h"
#include "task.h"
#include "util.h"
#include "simulate_queue.h"
#include <assert.h>
#include <math.h>

#define CAPACITY 20

void print_log(sim_log_t *log, size_t queue_size)
{
	printf(
			"---"
			"Processed %d tasks\n"
			"Processed %d tasks of first type\n"
			"Queue size: %zu\n"
			"Mean queue size: %u\n",
			log->tasks_out,
			log->tasks_out_1,
			queue_size,
			log->overall_len / log->tasks_out
	);
}


float fmean(float a, float b)
{
	return (a + b) / 2;
}


float ts_mean(timespan_t t)
{
	return fmean(t.low, t.high);
}

float await(timespan_t time)
{
	return rand_float(time.low, time.high);
}

void simulate(simulation_times_t times, int queue_kind)
{
	int pos_from_front = 4;
	int target_tasks = 1000;

	float fetch_time = 0;
	float work_time = 0;
	float hold_time = 0; // unused in this case

	float time_until_fetch = 0;
	float time_until_work = 0;

	queue_t queue = queue_new(queue_kind, sizeof(task_t), CAPACITY);
	sim_log_t log = { .tasks_in = 1 };

	task_t task_2 = task_new(2);
	queue_add(&queue, &task_2);

	while (log.tasks_out_1 != target_tasks)
	{
		// There will always be a second type task_to_process in the queue
		// but better assert
		assert(!queue_empty(&queue));

		// fetch a new task
		if (time_until_fetch == 0)
		{
			time_until_fetch = await(times.fetch);
			task_t new_task = task_new(1);
			if (queue_size(&queue) <= CAPACITY - 1) // leave space for 2nd task
			{
				queue_add(&queue, &new_task);
				log.tasks_in += 1;
			}
			else
				log.tasks_failed += 1;
			fetch_time += time_until_fetch;
		}

		//  process current task
		if (time_until_work == 0)
		{

			// if (queue_empty(&queue)) // does not happen here
			//	hold_time += time_until_fetch;
			// else
			// {
			task_t task_to_process = { 0 };
			queue_pop(&queue, &task_to_process);

			timespan_t work_timespan = task_to_process.type == 1 ? times.work_1 : times.work_2;
			time_until_work = await(work_timespan);

			work_time += time_until_work;
			log.tasks_out += 1;
			log.overall_len += queue_size(&queue);

			if (task_to_process.type == 1)
				log.tasks_out_1 += 1;
			else
			{
				log.calls += 1;
				log.tasks_in += 1;
				queue_insert_front(&queue, &task_to_process, pos_from_front);
			}
			if (log.tasks_out_1 % 100 == 0)
				print_log(&log, queue_size(&queue));
			// }
		}

		float smallest_time = fminf(time_until_work, time_until_fetch);
		time_until_work -= smallest_time;
		time_until_fetch -= smallest_time;
	}

	//if (print)
	//{
		float prob_sampling_second = 1.0f / (float) (pos_from_front);
		float prob_sampling_first = 1.0f - prob_sampling_second;
		float mean_work_rate = prob_sampling_first * ts_mean(times.work_1) \
                             + prob_sampling_second * ts_mean(times.work_2);
		float target_tasks_both_types = (float)target_tasks * (1 + prob_sampling_second);
		float expected_time = mean_work_rate * (float) target_tasks_both_types;
		float err = fabsf(work_time - expected_time) / expected_time * 100;


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

	queue_delete(&queue);
}

uint64_t simulate_profile(simulation_times_t times, int queue_kind)
{
	int pos_from_front = 4;
	int target_tasks = 1000;

	float time_until_fetch = 0;
	float time_until_work = 0;
	int tasks_out_1 = 0;

	uint64_t start = 0;
	uint64_t end = 0;

	queue_t queue = queue_new(queue_kind, sizeof(task_t), CAPACITY);

	start = ticks();

	task_t task_2 = task_new(2);
	queue_add(&queue, &task_2);

	while (tasks_out_1 != target_tasks)
	{

		// fetch a new task
		if (time_until_fetch == 0)
		{
			time_until_fetch = await(times.fetch);
			task_t new_task = task_new(1);
			if (queue_size(&queue) <= CAPACITY - 1) // leave space for 2nd task
			{
				queue_add(&queue, &new_task);
			}
		}

		//  process current task
		if (time_until_work == 0)
		{
			task_t task_to_process = { 0 };
			queue_pop(&queue, &task_to_process);

			timespan_t work_timespan = task_to_process.type == 1 ? times.work_1 : times.work_2;
			time_until_work = await(work_timespan);


			if (task_to_process.type == 2)
				queue_insert_front(&queue, &task_to_process, pos_from_front);
			else
				tasks_out_1 += 1;
		}

		float smallest_time = fminf(time_until_work, time_until_fetch);
		time_until_work -= smallest_time;
		time_until_fetch -= smallest_time;
	}
	end = ticks();
	queue_delete(&queue);

	return end-start;
}
