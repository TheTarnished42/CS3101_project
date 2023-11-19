// Will be completed Saturday afternoon.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "structs.h"
// #include "./cmn_fxns_book.c"

void print_categories(BOOK b)
{
    FILE *catptr;
    CAT c;
    catptr = fopen("./BooksDB/Categories.txt", "r+");
    int i = 0;
    printf("--Categories--\n");
    while (b.categories[i] != 0)
    {
        while (fread(&c, sizeof(CAT), 1, catptr))
        {
            if (c.no == b.categories[i])
                printf("%s\n", c.name);
        }
        i++;
        fseek(catptr, 0, SEEK_SET);
    }
    printf("\n");
    fclose(catptr);
}

int remove_book()
{
    char isbn[14];
    system("clear");
    printf("You are in Remove Book.\n");
    printf("Enter the isbn of book you want to edit: ");
    scanf("%s", isbn);
    getchar();
    long *searchres;
    searchres = searchBook2(isbn);

    BOOK b;
    FILE *bksptr;
    bksptr = fopen("./BooksDB/books.txt", "r+");
    fseek(bksptr, searchres[1], SEEK_SET);
    fread(&b, sizeof(BOOK), 1, bksptr);
    char isbn2[14];
    strcpy(isbn2, b.isbn);
    if (b.issued_copies != 0)
    {
        printf("Number of issued copies: %d\n", b.issued_copies);
        printf("To update a book's details, there should be no issued copies.\n");
        printf("Press Enter to continue.");
        getchar();
        return 0;
    }
    if (searchres[0] == 1)
    {
        printf("Existing Book Details:\n");
        printf("[1] ISBN: %s\n", b.isbn);
        printf("[2] Title: %s\n", b.title);
        printf("[3] Author: %s\n", b.author);
        printf("[4] Publisher: %s\n", b.publisher);
        print_categories(b);
        printf("Total Copies: %d\n\n", b.available_copies);
        // printf("If you wish to update the ISBN,enter[1]\n");
        printf("If you wish to update the above parameters, enter the corresponding number(1 or 2 or 3 or 4).\n");
        printf("If you wish to re-enter all of its categories, enter[5]. \n");
        printf("If you wish to remove this book(or reduce copies), enter [6].\n");
        printf("Enter 0 to go back to menu.\n");
        int *choice = malloc(sizeof(int));
        int flag = 0;

        do
        {
            printf("\nEnter your choice: ");
            scanf("%d", choice);
            getchar();
            printf("%d", *choice);
            if (*choice == 0)
            {
                return 0;
            }
            else if (*choice == 1)
            {
                printf("ISBN(5-digits): ");
                fgets(b.isbn, 14, stdin);
                b.isbn[strcspn(b.isbn, "\n")] = '\0';
                strcpy(isbn2, b.isbn);
            }
            else if (*choice == 2)
            {
                printf("Update Title: ");
                fgets(b.title, 100, stdin);
                b.title[strcspn(b.title, "\n")] = '\0';
            }
            else if (*choice == 3)
            {
                printf("Updated Author: ");
                fgets(b.author, 50, stdin);
                b.author[strcspn(b.author, "\n")] = '\0';
            }
            else if (*choice == 4)
            {
                printf("Updated Publisher: ");
                fgets(b.publisher, 50, stdin);
                b.publisher[strcspn(b.publisher, "\n")] = '\0';
            }
            else if (*choice == 5)
            {
                input_categories(&b);
            }
            else if (*choice == 6)
            {
                int copyno = 0;
                printf("Enter the number of copies to be removed: ");
                scanf("%d", &copyno);
                printf("%d\n", copyno);
                getchar();
                if (b.available_copies >= copyno)
                {

                    for (int i = b.available_copies; i >= 0; i--)
                    {
                        strcpy(b.available_UID[i - 1], b.available_UID[i]);
                    }
                    b.available_copies -= copyno;
                    char uid[10];
                    int n = searchres[0] / sizeof(BOOK);
                    for (int i = 1; i <= b.available_copies; i++)
                    {
                        sprintf(uid, "%d.%d", (n + 1), i);
                        strcpy(b.available_UID[i - 1], uid);
                    }
                    printf("%d Copies Removed.\n", copyno);
                }
                else
                {
                    printf("Not enough copies.\n");
                }
            }
            else
            {
                printf("Invalid input.\n");
            }

            int cnfm;
            printf("Confirm update[1], Re-enter or update another field[2], back-to-menu[0]: ");
            scanf("%d", &cnfm);
            if (cnfm == 1)
            {
                strcpy(b.isbn, isbn2);
                printf("%s\n", b.isbn);
                // printf("%ld\n", strlen(b.isbn));
                fseek(bksptr, -sizeof(BOOK), SEEK_CUR);
                fwrite(&b, sizeof(BOOK), 1, bksptr);
                printf("Updated.\n");
                printf("Press Enter to Continue");
                getchar();
                flag = 1;
            }
            if (cnfm == 0)
            {
                return 0;
            }
        } while (flag == 0);
        fclose(bksptr);
    }
    else
    {
        printf("Said isbn doesnot exist.\n");
    }
}
// void main()
// {
//     remove_book();
//     printf("\nExit2\n");
// }