#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <ctype.h>
/*This function includes the common functions called in remove_book and add_book*/

int *searchBook(char *isbn) // searches book by isbn
{
    // printf("In searchbook\n\n");
    FILE *fptr;
    BOOK b1;
    static int arr[2];
    arr[0] = 0;
    arr[1] = 0;
    fptr = fopen("./BooksDB/books.txt", "r+");

    while (fread(&b1, sizeof(BOOK), 1, fptr))
    {
        if (strcmp(isbn, b1.isbn) == 0)
        {
            // printf("\nBooks already exists!\n"); //printing existing book details.
            printf("Existing Book Details:\n");
            printf("[1] ISBN: %s\n", b1.isbn);
            printf("[2] Title: %s\n", b1.title);
            printf("[3] Author: %s\n", b1.author);
            printf("[4] Publisher: %s\n", b1.publisher);
            printf("Total Copies: %d\n\n", b1.available_copies);
            arr[0] = 1;
            arr[1] = ftell(fptr) - sizeof(BOOK);
            break;
        }
    }

    fclose(fptr);
    return arr;
}

void add_categories() // This is used to add new categories to the Database to choose from
{
    FILE *catptr;
    CAT c;
    c.no = 0;
    catptr = fopen("./BooksDB/Categories.txt", "r+"); // calling categories.txt
    while (fread(&c, sizeof(c), 1, catptr))
    {
    }
    c.no++;
    int flag = 0;
    printf("\nADD NEW CATEGORIES (Enter 0 to STOP ADDING CATEGORIES)\n\n"); // Accepting new categories

    while (flag == 0)
    {
        int flag2;
        while (1)
        {
            printf("NEW Category Name [%d]: ", (c.no)); // input
            fgets(c.name, 20, stdin);
            c.name[strcspn(c.name, "\n")] = '\0';
            if (c.name[0] == '0')
            {
                flag++;
                break;
            }
            while (1)
            {
                printf("Confirm New Category[1] or Enter Again[2]: "); // confirmation
                scanf("%d", &flag2);
                getchar();
                if (flag2 == 1)
                {
                    fwrite(&c, sizeof(c), 1, catptr);
                    c.no++;
                    printf("Category ADDED.\n\n");
                    break;
                }
                else if (flag2 == 2)
                   { printf("Enter Again.\n");
                        break;}
                else
                    printf("Invalid input.\n");
            }
        }
        printf("Exited from ADD NEW CATEGORIES.\n"); // exit
    }
    fclose(catptr);
}

void input_categories(BOOK *b) // this is used to assign categories to books added by admin.
{

    printf("#---------------------------------------------------------#\n");
    FILE *catptr;
    CAT c;
    catptr = fopen("./BooksDB/Categories.txt", "r+");
    printf("--EXISTING CATEGORIES--\n"); // printing existing categories
    while (fread(&c, sizeof(c), 1, catptr))
    {
        printf("[%d] %s\n", c.no, c.name);
    }
    printf("-----------------------\n");
    fclose(catptr);
    char yn[1];
    while (1)
    {
        printf("\nDo you wish to ADD a NEW CATEGORY to the above list? [y/n]: "); // redirects to add_categories based on input
        scanf("%s", yn);
        if (tolower(yn[0]) == 'y')
        {
            getchar();
            add_categories();
            break;
        }
        else if (tolower(yn[0]) == 'n')
        {
            break;
        }
        else
            printf("Invalid Input.\n");
    }
    if (tolower(yn[0]) == 'y')
    {
        catptr = fopen("./BooksDB/Categories.txt", "r+"); // printing with new categories added
        printf("\n--EXISTING CATEGORIES (UPDATED)--\n");
        while (fread(&c, sizeof(c), 1, catptr))
        {
            printf("[%d] %s\n", c.no, c.name);
        }
        printf("\n--------------------------------\n");
        fclose(catptr);
    }
    printf("Multiple Categories can be assigned to one Book.\n"); // disclaimer
    printf("\nAssign Category to the book by entering SERIAL NUMBER as per the above list.\nENTER 0 to STOP assigning.\n");

    while (1) // assigning categories to books
    {
        int counter = 0;
        int sno[50];
        while (1)
        {

            printf(" [%d] Assign Category: ", (counter + 1));
            scanf("%d", &sno[counter]);
            if (sno[counter] == 0)
                break;
            else
                counter++;
        }
        counter = 0;
        printf("\nSerial Numbers of the Categories Assigned to the Book: "); // for confirmation
        while (sno[counter] != 0)
        {
            printf("%d ", sno[counter]);
            counter++;
        }
        counter = 0;
        printf("\nConfirm Book Categories? [y/n]: ");
        scanf("%s", yn);
        if (tolower(yn[0]) == 'y')
        {
            while (sno[counter] != 0) // updating categories of the book variable
            {
                b->categories[counter] = sno[counter];
                b->categories[counter + 1] = 0; // Line added here by Ahan
                counter++;
            }
            printf("Book Categories Confirmed.\n");
            break;
        }
        else if (tolower(yn[0]) == 'n')
        {
            printf("Re-enter[1] Don't Assign Categories[0]?: "); // categories assigned
            scanf("%d", &counter);
            if (counter == 0)
                break;
            else
                printf("Re-ENTRY\n");
        }
    }
    printf("#----------------------------------------------------------#\n\n");
}

long *searchBook2(char *isbn) // differs from searchbook() in that it does not print the book matched
{
    // printf("In searchbook\n\n");
    FILE *fptr;
    BOOK b1;
    static long arr[2];
    arr[0] = 0;
    arr[1] = 0;
    fptr = fopen("./BooksDB/books.txt", "r+");

    while (fread(&b1, sizeof(BOOK), 1, fptr))
    {
        if (strcmp(isbn, b1.isbn) == 0)
        {
            arr[0] = 1;
            arr[1] = ftell(fptr) - sizeof(BOOK);
            break;
        }
    }

    fclose(fptr);
    return arr;
}