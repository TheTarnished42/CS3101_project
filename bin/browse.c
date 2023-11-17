
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <unistd.h>
#include "structs.h"
// #include "member_menu.c"

int unique_index;

long *searchByCategories()
{
    FILE *catptr = fopen("../BooksDB/Categories.txt", "r+");
    CAT c;
    system("clear");
    printf("----------EXISTING CATEGORIES----------\n\n");
    while (fread(&c, sizeof(c), 1, catptr))
    {
        printf("[%d] %s\n", c.no, c.name);
    }

    printf("\n\n----------xxxxxxxxxx----------\n\n");

    int cat[c.no];
    int count = 0;
    int num;
    int flag = 0;
    while (1)
    {
        while (1)
        {
            printf("\nEnter category number(s) (Enter 0 to stop): ");
            scanf("%d", &num);
            if (num == 0)
            {
                break;
            }
            if (num > c.no || num < 0)
            {
                printf("\nInvalid entry. Re-enter this entry...\n");
                continue;
            }
            for (int i = 0; i < count; i++)
            {
                if (cat[i] == num)
                {
                    printf("\nYou have already entered this category...\n");
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                flag = 0;
                continue;
            }
            cat[count] = num;
            count++;
        }

        int k = 0;
        printf("\n--------------------\n");
        printf("\nPrinting categories entered: ");
        for (int i = 0; i < count; i++)
        {
            printf("%d ", cat[k]);
            k++;
        }
        printf("\n");
        printf("\nEnter 1 to confirm and 0 to re-enter your entries: ");
        int reenter;
        scanf("%d", &reenter);
        if (reenter == 1)
        {
            system("clear");
            break;
        }
        else
        {
            count = 0;
        }
    }

    system("clear");
    printf("====================");
    printf("\nCategories confirmed: ");
    int k = 0;

    for (int i = 0; i < count; i++)
    {
        fseek(catptr, 0, SEEK_SET);
        while (fread(&c, sizeof(c), 1, catptr))
        {
            if (c.no == cat[k])
            {
                printf("%s ", c.name);
            }
        }
    }
    printf("\n");

    // Now printing all the books in the mentioned categories:
    long *arr_ftells = NULL; // Declare a pointer for dynamic allocation
    int max_elements = 10;
    arr_ftells = (long *)malloc(max_elements * sizeof(long));
    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
    BOOK b;
    int index = 0;
    while (fread(&b, sizeof(BOOK), 1, fptr))
    {
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                if (cat[i] == b.categories[j])
                {
                    // Check if more memory is needed
                    if (index >= max_elements)
                    {
                        // Increase the size of the array using realloc
                        max_elements *= 2; // Double the size
                        arr_ftells = (long *)realloc(arr_ftells, max_elements * sizeof(long));
                    }

                    // Store the pointer position
                    arr_ftells[index] = ftell(fptr);
                    index++;
                }
            }
        }
    }

    unique_index = 0;
    for (int i = 0; i < index; i++)
    {
        int duplicate = 0;
        for (int j = 0; j < unique_index; j++)
        {
            if (arr_ftells[i] == arr_ftells[j])
            {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate)
        {
            arr_ftells[unique_index] = arr_ftells[i];
            unique_index++;
        }
    }

    // Resize arr_ftells to the number of unique elements
    arr_ftells = (long *)realloc(arr_ftells, unique_index * sizeof(long));

    // Print the elements of the array
    system("clear");
    printf("Elements of the array:\n\n");
    for (int i = 0; i < unique_index; i++)
    {
        printf("%ld ", arr_ftells[i]);
    }
    printf("\n");

    // Return the dynamically allocated array
    return arr_ftells;
}

void dataSearch(int choice, char str[100])
{
    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
    BOOK b;
    switch (choice)
    {
    case 2:

        break;

    default:
        break;
    }
}

int search()
{
    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
    BOOK b;
    system("clear");
    printf("\nYou have chosen to search for a book.\n\n");
    printf("Enter '1' to search by category\n");
    printf("Enter '2' to search by name of the book\n");
    printf("Enter '3' to search by name of the author(s)\n");
    printf("Enter '4' to search by ISBN code of the book\n");
    printf("Enter '5' to go back to menu\n");

    int choice;
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            long *result = searchByCategories();
            printf("\nThe following books are available:\n==============================\n");
            for (int i = 0; i < unique_index; i++)
            {
                fseek(fptr, result[i] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("\n[%d]: %s by %s; ISBN: %lld; No. of copies available: %d", (i + 1), b.title, b.author, b.isbn, b.available_copies);
            }
            printf("\n\n");
            printf("\n\n==============================\n");

            printf("\n");

            return 1;
        case 2:
            char name_of_book[100];
            printf("\nEnter the name of the book: ");
            fgets(name_of_book, 100, stdin);
            name_of_book[strcspn(name_of_book, "\n")] = '\0';
            dataSearch(choice, name_of_book);
            return 1;

        case 3:
            char name_of_auth[100];
            printf("\nEnter the name of the author: ");
            fgets(name_of_auth, 50, stdin);
            name_of_auth[strcspn(name_of_auth, "\n")] = '\0';
            dataSearch(choice, name_of_auth);
            return 1;

        case 4:
            char isbn[100];

            printf("\nEnter the ISBN code of the book: ");
            fgets(isbn, 14, stdin);
            isbn[strcmp(isbn, "\n")] = '\0';
            dataSearch(choice, isbn);
            return 1;

        case 5:
            return -1;
        default:
            system("clear");
            printf("Wrong choice! Enter again...\n\n");
            printf("Enter '1' to search by category\n");
            printf("Enter '2' to search by name of the book\n");
            printf("Enter '3' to search by name of the author(s)\n");
            printf("Enter '4' to search by ISBN code of the book\n");
            printf("Enter '5' to go back to menu\n");
        }
    }
}

void main()
{

    int a = search();
}