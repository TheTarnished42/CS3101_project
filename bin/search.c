#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
//#include "member_menu.c"

int search()
{
    extern int *usertype;
    system("clear");
    printf("\nYou have chosen to search for a book.\n\n");
    printf("Enter '1' to search by name of the book\n");
    printf("Enter '2' to search by name of the author(s)\n");
    printf("Enter '3' to search by ISBN code of the book\n");
    printf("Enter '4' to go back to menu\n");
    printf("Enter your choice: ");
    int choice;
    while (1)
    {
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Case 1!!!");
            break;
        case 2:
            printf("Case 2!!!");
            break;
        case 3:
            printf("Case 3!!!");
            break;
        case 4:
            return 0;
        default:
            system("clear");
            printf("Wrong choice! Enter again...");
            printf("\nYou have chosen to search for a book.\n\n");
            printf("Enter '1' to search by name of the book\n");
            printf("Enter '2' to search by name of the author(s)\n");
            printf("Enter '3' to search by ISBN code of the book\n\n");
            printf("Enter '4' to go back to menu\n");
            printf("Enter your choice: ");
        }
    }
}

void main()
{
    int a = search();
}