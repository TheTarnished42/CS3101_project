// Will be completed Saturday afternoon.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "structs.h"

long *searchBook2(char *isbn)
{
    printf("In searchbook\n\n");
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
            printf("\nBooks exists at position %ld!\n", ftell(fptr) / sizeof(BOOK));
            // printf("Title: %s\n", b1.title);
            // printf("Author: %s\n", b1.author);
            // printf("Publisher: %s\n", b1.publisher);
            arr[0] = 1;
            arr[1] = ftell(fptr) - sizeof(BOOK);
            break;
        }
    }

    fclose(fptr);
    return arr;
}
void add_categories2()
{
    FILE *catptr;
    CAT c;
    c.no = 0;
    catptr = fopen("./BooksDB/Categories.txt", "r+");
    while (fread(&c, sizeof(c), 1, catptr))
    {
    }
    c.no++;
    int flag = 0;
    printf("\nADD NEW CATEGORIES: Enter 0 to QUIT\n\n");

    while (flag == 0)
    {
        int flag2;
        while (1)
        {
            printf("NEW Category Name [%d]: ", (c.no));
            fgets(c.name, 20, stdin);
            c.name[strcspn(c.name, "\n")] = '\0';
            if (c.name[0] == '0')
            {
                flag++;
                break;
            }
            while (1)
            {
                printf("Confirm New Category[1] or Enter Again[2]: ");
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
                    printf("Enter Again.\n");
                else
                    printf("Invalid input.\n");
            }
        }
        printf("Exited from ADD NEW CATEGORIES.\n");
    }
    fclose(catptr);
}
void input_categories2(BOOK *b)
{

    printf("#---------------------------------------------------------#\n");
    FILE *catptr;
    CAT c;
    catptr = fopen("./BooksDB/Categories.txt", "r+");
    printf("--EXISTING CATEGORIES--\n");
    while (fread(&c, sizeof(c), 1, catptr))
    {
        printf("[%d] %s\n", c.no, c.name);
    }
    printf("\n--EXISTING CATEGORIES--\n");
    fclose(catptr);
    char yn[1];
    while (1)
    {
        printf("\nDo you wish to ADD a NEW CATEGORY to the above list? [y/n]: ");
        scanf("%s", yn);
        if (tolower(yn[0]) == 'y')
        {
            getchar();
            add_categories2();
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
        catptr = fopen("./BooksDB/Categories.txt", "r+");
        printf("\n--EXISTING CATEGORIES--\n");
        while (fread(&c, sizeof(c), 1, catptr))
        {
            printf("[%d] %s\n", c.no, c.name);
        }
        printf("\n--EXISTING CATEGORIES--\n");
        fclose(catptr);
    }
    printf("\nAssign Category to the book by the corresponding SERIAL NUMBER. \nENTER 0 to STOP assigning.\n");

    while (1)
    {
        int counter = 0;
        int sno[50];
        while (1)
        {

            printf("  Assign %dth category of the book(by serial number): ", (counter + 1));
            scanf("%d", &sno[counter]);
            if (sno[counter] == 0)
                break;
            else
                counter++;
        }
        counter = 0;
        printf("\nEntered Categories: ");
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
            while (sno[counter] != 0)
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
            printf("Re-enter[1] Exit[0]: ");
            scanf("%d", &counter);
            if (counter == 0)
                break;
            else
                printf("Re-ENTRY\n");
        }
    }
    printf("#----------------------------------------------------------#\n\n");
}

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
        printf("If you wish to update the ISBN,enter[1]\n");
        printf("If you wish to update the above parameters, enter the corresponding number(2,3,4).\n");
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
                input_categories2(&b);
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
            printf("Confirm update[1], Re-enter or update another field[2], back-to-menu[3]: ");
            scanf("%d", &cnfm);
            if (cnfm == 1)
            {
                strcpy(b.isbn, isbn2);
                printf("%s\n", b.isbn);
                // printf("%ld\n", strlen(b.isbn));
                fseek(bksptr, -sizeof(BOOK), SEEK_CUR);
                fwrite(&b, sizeof(BOOK), 1, bksptr);
                printf("Updated.\n");
                flag = 1;
            }
            if (cnfm == 3)
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