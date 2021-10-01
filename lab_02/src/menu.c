#include "menu.h"
#include <stdio.h>

int get_choice(int argc, char **argv)
{
    int choice = -1;
    while (choice < 0)
    {
        for (int i = 0; i < argc; i++)
        {
            printf("%d: %s\n", i, argv[i]);
        }
        printf("Your choice: ");
        scanf("%d", &choice);
        if (choice < 0 || choice > argc-1)
            choice = -1;
    }
    return choice;
}
