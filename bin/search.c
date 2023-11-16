#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
// #include "member_menu.c"

void dataSearch(char str[100])
{
    printf("Here!");
}

int search()
{
    system("clear");
    printf("\nYou have chosen to search for a book.\n\n");
    printf("Enter '1' to search by name of the book\n");
    printf("Enter '2' to search by name of the author(s)\n");
    printf("Enter '3' to search by ISBN code of the book\n");
    printf("Enter '4' to go back to menu\n");
    
    int choice;
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            char name_of_book[100];
            printf("\nEnter the name of the book: ");
            fgets(name_of_book, 100, stdin);
            name_of_book[strcspn(name_of_book, "\n")] = '\0';
            dataSearch(name_of_book);
            return 1;

        case 2:
            char name_of_auth[100];
            printf("\nEnter the name of the author: ");
            fgets(name_of_auth, 50, stdin);
            name_of_auth[strcspn(name_of_auth, "\n")] = '\0';
            dataSearch(name_of_auth);
            return 1;

        case 3:
            char isbn[100];

            printf("\nEnter the ISBN code of the book: ");
            fgets(isbn, 14, stdin);
            isbn[strcmp(isbn, "\n")] = '\0';
            dataSearch(isbn);
            return 1;

        case 4:
            return 0;
        default:
            system("clear");
            printf("Wrong choice! Enter again...");
            printf("Enter '1' to search by name of the book\n");
            printf("Enter '2' to search by name of the author(s)\n");
            printf("Enter '3' to search by ISBN code of the book\n\n");
            printf("Enter '4' to go back to menu\n");
        }
    }
}

void main()
{
    int a = search();
}