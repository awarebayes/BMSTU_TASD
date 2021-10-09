#include "menu.h"
#include "table.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_CHOICE 123
#define TIMES 50

char *key_types[] = {"Lastname", "Title", "Publisher", "Pages", "Type"};

int get_choice(int argc, char **argv)
{
    int choice = -1;
    while (choice < 0)
    {
        int ec = 0;
        for (int i = 0; i < argc; i++)
        {
            printf("%d: %s\n", i, argv[i]);
        }
        printf("%d: EXIT\n", EXIT_CHOICE);
        read_int(stdout, "Your choice: ", &choice, stdin, &ec);
        if (ec)
        {
            choice = -1;
            continue;
        }
        if (choice < 0 || (choice > argc - 1 && choice != EXIT_CHOICE))
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
    void *ptr = NULL;
    int ec = ok;
    size_t size = 0;
    if (base_type == key_int)
    {
        int *a = malloc(sizeof(int));
        read_int(stdout, "Your key (int): ", a, stdin, &ec);
        ptr = a;
        size = sizeof(int);
    }
    if (base_type == key_string)
    {
        char *buf = malloc(sizeof(char) * 128);
        read_str(stdout, "Your key (str): ", buf, stdin, &ec);
        ptr = buf;
        size = sizeof(char) * (strlen(buf) + 1);
    }
    if (ec)
    {
        free(ptr);
        return get_key();
    }
    return key_new(type, ptr, size, 0);
}

sort_func_t choose_sort()
{
    int choice = -1;
    int ec = ok;
    while (choice != 0 && choice != 1)
    {
        printf("How would you like to sort?\n");
        printf("0. Bubble sort, O(n^2)\n");
        printf("1. QSort, O(nlogn)\n");
        read_int(stdout, "Your sort (int): ", &choice, stdin, &ec);
    }
    if (ec)
        return choose_sort();
    else if (choice == 0)
        return insert_sort;
    return qsort;
}

void ask_update_key_table(table_t *table, int *update_flag)
{
    int type = choose_key_type();
    table_update_keys(table, type);
    *update_flag = 0;
}

void menu_filter(table_t *table)
{
    book_key_t key = get_key();
    int n = 0;
    int *indexes = table_filter(table, &key, &n);
    if (n != 0)
        table_print_at_indexes(table, indexes, n);
    else
        printf("No matches found!\n");
    key_delete(&key);
    free(indexes);
}

void menu_remove(table_t *table)
{
    book_key_t key = get_key();
    int n = 0;
    int *indexes = table_filter(table, &key, &n);
    if (n != 0)
        table_remove(table, indexes, n);
    else
        printf("Nothing to remove!\n");
    key_delete(&key);
    free(indexes);
}

void menu_filter_year(table_t *table)
{
    int year = 0;
    int ec = 0;
    char book_buf[1024];
    char field[1024];

    do
    {
        read_int(stdout, "Your year (int): ", &year, stdin, &ec);
        read_str(stdout, "Your field (str): ", field, stdin, &ec);
    }
    while (ec != 0);
    int n = 0;
    int *indexes = table_filter_tech_year(table, year, field, &n);
    if (n != 0)
    {
        printf("Found %d books\n", n);
        for (int i = 0; i < n; i++)
        {
            book_show(book_buf, &table->books[indexes[i]]);
            printf("%s\n", book_buf);
        }
    }
    else
        printf("Nothing found!\n");
    free(indexes);
}

void read_table_given_path(table_t *table, char *path, int *ec)
{
    int n = 0;
    table_t temp_table = {0};
    FILE *f = fopen(path, "r");
    if (f == NULL)
        *ec = file_err;
    if (!*ec)
    {
        read_int(NULL, "", &n, f, ec);
        if (n == 0)
            *ec = file_err;
        temp_table = table_read_file(f, n, ec);
    }
    if (!(*ec))
        *table = temp_table;
    if(f)
        fclose(f);
    if (*ec != ok)
    {
        printf("On read an error occured with code: %d\n", *ec);
        return;
    }
}

void menu_read_file(table_t *table, int *ec)
{
    char fstr[1024];
    read_str(stdout, "File path: ", fstr, stdin, ec);
    read_table_given_path(table, fstr, ec);
}

void menu_serialize_file(table_t *table, int *ec)
{
    char fstr[1024];
    read_str(stdout, "File path: ", fstr, stdin, ec);

    FILE *f = fopen(fstr, "w");
    if (f == NULL)
        *ec = file_err;
    if (!(*ec))
        table_serialize_file(table, f);
    if (*ec)
        printf("Unable to serialize!\n");
    if (f)
        fclose(f);
}

void menu_profile()
{
    int sizes[] = {50, 100, 300, 500, 1000};
    int n = sizeof(sizes)/sizeof(sizes[0]);
    size_t main_ins[n];
    size_t main_qsort[n];
    size_t keys_ins[n];
    size_t keys_qsort[n];

    // Main table
    for (int i = 0; i < n; i++)
        main_ins[i] = sorting_time_mean(sorting_time_table_ns, insert_sort, sizes[i], TIMES);
    for (int i = 0; i < n; i++)
        main_qsort[i] = sorting_time_mean(sorting_time_table_ns, qsort, sizes[i], TIMES);
    
    // Keys
    for (int i = 0; i < n; i++)
        keys_ins[i] = sorting_time_mean(sorting_time_keys_ns, insert_sort, sizes[i], TIMES);
    for (int i = 0; i < n; i++)
        keys_qsort[i] = sorting_time_mean(sorting_time_keys_ns, qsort, sizes[i], TIMES);

    printf("Time (ticks)\n");
    printf("%-3s, %-5s, %-10s, %-10s, %-10s, %-10s\n", "idx", "size", "main_ins", "main_qsort", "keys_ins", "keys_qsort");
    for (int i = 0; i < n; i++)
        printf("%-3d, %-5d, %-10ld, %-10ld, %-10ld, %-10ld\n", i, sizes[i], main_ins[i], main_qsort[i], keys_ins[i], keys_qsort[i]);

    printf("\nMemory (bytes)\n");
    printf("%-7s, %-10s, %-10s\n", "size(n)", "table", "keys");
    for (int i = 0; i < n; i++)
    {
        table_t t = table_new(sizes[i]);
        printf("%-7d, %-10ld, %-10ld\n", sizes[i], table_size(&t), table_keys_size(&t));
        table_delete(&t);
    }
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
        "Delete entry",
        "Profile",
        "Write table",
        "Filter tech books with specified year"
        };
    int type = 0;
    int ec = ok;
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
            menu_read_file(table, &ec);
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
            if (need_update)
                ask_update_key_table(table, &need_update);
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
            menu_filter(table);
            break;
        case 9:
            menu_remove(table);
            break;
        case 10:
            menu_profile();
            break;
        case 11:
            ec = ok;
            menu_serialize_file(table, &ec);
            if (ec)
                printf("Problem serializing...\n");
            break;
        case 12:
            menu_filter_year(table);
            break;
        default:
            break;
        }
    }
}