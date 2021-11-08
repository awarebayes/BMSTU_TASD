//
// Created by dev on 11/2/21.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <menu.h>
#include "memory.h"
#include "tests.h"
#include "simulate_queue.h"
#include "queue.h"

int main()
{
	srand(time(NULL));   // Initialization, should only be called once.
	log_init();
	check_all();
	main_loop();
}
