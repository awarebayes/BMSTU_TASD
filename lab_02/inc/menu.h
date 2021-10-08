#ifndef __MENU_H__
#define __MENU_H__
#include "table.h"

int get_choice(int argc, char **argv);
void act_on_table(table_t *table);
void read_table_given_path(table_t *table, char *fstr, int *ec);

#endif // !__MENU_H__