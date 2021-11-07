//
// Created by dev on 11/3/21.
//

#ifndef LAB_05_SOLUTION_H
#define LAB_05_SOLUTION_H

typedef struct
{
	float low;
	float high;
} timespan_t;

typedef struct
{
	timespan_t await;
	timespan_t work_1;
	timespan_t work_2;
} simulation_times_t;

typedef struct
{
	int tasks_in;
	int tasks_out;
	int tasks_out_1;
	int tasks_failed;
	int calls;
	int overall_len;
} sim_log_t;

// queue_kind определён в queue_h: list / vector queue
void simulate(simulation_times_t times, int queue_kind);

#endif //LAB_05_SOLUTION_H
