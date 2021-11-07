//
// Created by dev on 10/21/21.
//

#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void log_init(void)
{
	deleted_addresses = calloc(LOG_SIZE, sizeof(void *));
}

void log_delete(void* address)
{
	if (log_index >= LOG_SIZE)
		log_index = 0;
	deleted_addresses[log_index++] = address;
}

void log_print_deleted_addresses(void)
{
	printf("Deleted Addresses:\n");
	if (log_index == 0)
	{
		printf("No addresses yet!\n");
		return;
	}
	int offset = 0;
	printf("address        offset\n");
	for (int i = 0; i < log_index; i++)
	{
		printf("%p %d\n", deleted_addresses[i], offset);
		offset = (char*)deleted_addresses[i+1] - (char*)deleted_addresses[i];
	}
	printf("\n");
}
