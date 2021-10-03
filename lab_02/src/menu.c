#include "menu.h"
#include "table.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#define EXIT_CHOICE 123

char *key_types[] = {"Lastname", "Title", "Publisher", "Pages", "Type"};

int get_choice(int argc, char **argv)
{
    int choice = -1;
    while (choice < 0)
    {
        for (int i = 0; i < argc; i++)
        {
            printf("%d: %s\n", i, argv[i]);
        }
        printf("%d: EXIT\n", EXIT_CHOICE);
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice < 0 || (choice > argc-1 && choice != EXIT_CHOICE))
            choice = -1;
    }
    return choice;
}

int choose_key_type()
{
    printf("Choose a key type:\n");
    return get_choice(sizeof(key_types) / sizeof(char *), key_types);
}

book_key_t get_key()
{
    int type = choose_key_type();
    int base_type = get_base_type(type);
    void *ptr;
    if (base_type == key_int)
    {
        int *a = malloc(sizeof(int));
        scanf("%d", a);
        ptr = a;
    }
    if (base_type == key_string)
    {
        char *buf = malloc(sizeof(char) * 128);
        scanf("%s", buf);
        ptr = buf;
    }
    return key_dummy(type, ptr);
}

sort_func_t choose_sort()
{
    int choice = -1;
    while (choice != 0 && choice != 1)
    {
        printf("How would you like to sort?\n");
        printf("0. Bubble sort, O(n^2)\n");
        printf("1. QSort, O(nlogn)\n");
        scanf("%d", &choice);
    }
    if (choice == 0)
        return insert_sort;
    return qsort;
}

void ask_update_key_table(table_t *table, int *update_flag)
{
    int type = choose_key_type();
    table_update_keys(table, type);
    *update_flag = 0;
}

void act_on_table(table_t *table)
{
    int choice = 0;
    char *choices[] = {
        "Read table from file",
        "Print table",
        "Print keys",
        "Print table indexed by keys",
        "Add to table",
        "Update key table",
        "Sort table",
        "Sort key table",
        "Filter entries",
        "Delete entry"};
    int type = 0;
    int ec = ok;
    book_key_t key = {0};
    int n = 0;
    int *indexes = NULL;
    int need_update = 1;
    while (choice != EXIT_CHOICE)
    {
        printf("\n");
        choice = get_choice(sizeof(choices) / sizeof(char *), choices);
        printf("\n");
        switch (choice)
        {
        case 0:
            ec = ok;
            FILE *f = fopen("../tests/input.txt", "r");
            *table = table_read_file(f, 8, &ec);
            need_update = 1;
            break;
        case 1:
            table_print(table);
            break;
        case 2:
            if (need_update)
                ask_update_key_table(table, &need_update);
            table_print_key_table(table);
            break;
        case 3:
            table_print_proxy(table);
            break;
        case 4:
            ec = ok;
            book_t book = book_read(stdin, stdout, &ec);
            if (!ec)
                table_insert(table, book);
            else
                printf("Occured error with code: %d\n", ec);
            need_update = 1;
            break;
        case 5:
            type = choose_key_type();
            table_update_keys(table, type);
            need_update = 0;
            break;
        case 6:
            type = choose_key_type();
            table_sort(table, choose_sort(), type);
            need_update = 1;
            break;
        case 7:
            if (need_update)
                ask_update_key_table(table, &need_update);
            table_sort_keys(table, choose_sort());
            break;
        case 8:
            key = get_key();
            n = 0;
            indexes = table_filter(table, &key, &n);
            table_print_at_indexes(table, indexes, n);
            key_delete(&key);
            free(indexes);
            break;
        case 9:
            key = get_key();
            n = 0;
            indexes = table_filter(table, &key, &n);
            table_remove(table, indexes, n);
            key_delete(&key);
            free(indexes); 
        default:
            break;
        }
    }
}