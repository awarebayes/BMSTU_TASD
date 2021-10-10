#include "menu.h"
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



void main_loop()
{
    int choice = 0;
    char *choices[] = {
        "Read matrix (as dense)",
        "Read matrix (as sparse)",
        "Read vector (as dense)",
        "Read vector (as sparse)",
        "Muiltiply matrix (as sparse)",
        "Muiltiply matrix (as sparse)",
        "Profile",
        };
    int ec = ok;
    while (choice != EXIT_CHOICE)
    {
        printf("\n");
        choice = get_choice(sizeof(choices) / sizeof(char *), choices);
        printf("\n");
        switch (choice)
        {
        case 1:
            break;
        default:
            break;
        }
    }
}