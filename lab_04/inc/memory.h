//
// Created by dev on 10/21/21.
//

#ifndef LAB_04_MEMORY_H
#define LAB_04_MEMORY_H

static void **deleted_addresses;
static int log_index = 0;
#define LOG_SIZE 1000
#define LOG_DELETED 1

void log_init(void);

void log_delete(void* address);

void log_print_deleted_addresses(void);

#endif //LAB_04_MEMORY_H
