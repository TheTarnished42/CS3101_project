#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <ctype.h>
// #include "./browse.c"

int *searchBook(char *isbn)
{
    printf("In searchbook\n\n");
    FILE *fptr;
    BOOK b1;
    static int arr[2];
    arr[0] = 0;
    arr[1] = 0;
    fptr = fopen("../BooksDB/books.txt", "r+");

    while (fread(&b1, sizeof(BOOK), 1, fptr))
    {
        if (strcmp(isbn, b1.isbn) == 0)
        {
            printf("\nBooks already exists at position %ld!\n", ftell(fptr));
            arr[0] = 1;
            arr[1] = ftell(fptr) - sizeof(BOOK);
            break;
        }
    }

    fclose(fptr);
    return arr;
}
void add_categories()
{
    FILE *catptr;
    CAT c;
    c.no = 0;
    catptr = fopen("../BooksDB/Categories.txt", "r+");
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

int uid_and_overwrite(BOOK *b, int *searchres)
{
    BOOK b2;
    FILE *uniq;
    int n = 0;
    uniq = fopen("../BooksDB/books.txt", "r+");
    while (fread(&b2, sizeof(BOOK), 1, uniq))
    {
        n++;
    }
    if (searchres[0] == 1)
    {
        int n2 = searchres[1] / sizeof(BOOK) + 1;
        fseek(uniq, searchres[1], SEEK_SET);
        fread(&b2, sizeof(BOOK), 1, uniq);
        char uid[10];
        int i2 = 0;
        int total_copies = b2.available_copies + b2.issued_copies;
        while (strcmp(b2.available_UID[i2], "\0") != 0)
        {
            i2++;
        }
        for (int i = 0; i < b->available_copies; i++)
        {
            sprintf(uid, "%d.%d", n2, (i + 1 + total_copies));
            strcpy(b2.available_UID[i2 + i], uid);
        }
        b2.available_copies += b->available_copies;
        // strcpy(b2.available_UID[total_copies + b->available_copies], '\0');
        fseek(uniq, -sizeof(BOOK), SEEK_CUR);
        fwrite(&b2, sizeof(BOOK), 1, uniq);
    }
    else
    {
        printf("New Book.\n");
        char uid[10];
        fseek(uniq, 0, SEEK_END);
        for (int i = 1; i <= b->available_copies; i++)
        {
            sprintf(uid, "%d.%d", (n + 1), i);
            strcpy(b->available_UID[i - 1], uid);
        }
        // strcpy(b->available_UID[b->available_copies], "\0");
        b->issued_copies = 0;
        // strcpy(b->issued_UID[0], '\0');
        fwrite(b, sizeof(BOOK), 1, uniq);
    }
    fclose(uniq);
}

void input_categories(BOOK *b)
{

    printf("#---------------------------------------------------------#\n");
    FILE *catptr;
    CAT c;
    catptr = fopen("../BooksDB/Categories.txt", "r+");
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
        catptr = fopen("../BooksDB/Categories.txt", "r+");
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

int add_book()
{
    printf("You are in Add Book.\n");
    BOOK b1;
    // b1 is the input structure.
    int flag_input = 0;
    int *search_result;
    do
    { // input
        printf("ISBN(5-digits): ");
        fgets(b1.isbn, 14, stdin);
        b1.isbn[strcspn(b1.isbn, "\n")] = '\0';

        search_result = searchBook(b1.isbn);
        if (search_result[0] == 1)
        {
            char yn;
            printf("Book Already Exists!");
            // display_book();
            printf("Is this the Book whose stock is to be increased? [y/n]: ");
            scanf("%c", &yn);
            getchar();
            if (tolower(yn) == 'y')
            {
                printf("Number of Copies: ");
                scanf("%d", &b1.available_copies);
                getchar();
                break;
            }
            else
            {
                printf("Enter ISBN again.\n");
                continue;
            }
        }
        printf("Enter the Book details:\nTitle: ");
        fgets(b1.title, 100, stdin);
        b1.title[strcspn(b1.title, "\n")] = '\0';

        printf("Author: ");
        fgets(b1.author, 50, stdin);
        b1.author[strcspn(b1.author, "\n")] = '\0';

        printf("Publisher: ");
        fgets(b1.publisher, 50, stdin);
        b1.publisher[strcspn(b1.publisher, "\n")] = '\0';

        input_categories(&b1);

        printf("Number of Copies: ");
        scanf("%d", &b1.available_copies);

        while (1)
        {
            printf("\nConfirm Input[1] , Re-enter[2] or back-to-menu[3]?: ");
            int cnfm;
            scanf("%d", &cnfm);
            if (cnfm == 3)
                return 0;
            else if (cnfm == 2)
            {
                printf("\n---RE_ENTRY---\n");
                break;
            }
            else if (cnfm == 1)
            {
                printf("Entry Confirmed\n");
                flag_input++;
                break;
            }
            else
                printf("Invalid input, Choose again.\n");
        }
        getchar();
    } while (flag_input == 0);
    // Input Complete. Now we update the books.txt file.

    /*IMPORTANT: We must call a search fxn from browse.c to check if the title already exits.
      And, return must be a flag(that says yes or no) and fseek offset
    */

    printf("Returned Values: %d, %d\n", search_result[0], search_result[1]);
    uid_and_overwrite(&b1, search_result);
    return 0;
}

void main()
{
    // add_book();
    FILE *fptr;
    BOOK b1;
    fptr = fopen("../BooksDB/books.txt", "r+");
    fread(&b1, sizeof(BOOK), 1, fptr);
    fread(&b1, sizeof(BOOK), 1, fptr);
    printf("%s", b1.available_UID[6]);
    printf("\nExit\n");
}
