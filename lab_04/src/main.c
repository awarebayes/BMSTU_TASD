//
// Created by dev on 10/21/21.
//

#include <stdio.h>
#include "tests.h"
#include "memory.h"
#include "menu.h"

int main()
{
	if (LOG_DELETED)
		log_init();
	check_all();
	main_loop();
}
