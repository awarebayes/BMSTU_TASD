//
// Created by dev on 11/3/21.
//

#include "task.h"
#include <stdlib.h>

task_t task_new(int type)
{
	task_t self = { .type = type };
	return self;
}
