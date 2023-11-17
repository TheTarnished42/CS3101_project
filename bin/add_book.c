#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Declaring the book structure.
typedef struct book
{
    char ISBN[6];
    char title[100];
    char author[50];
    char publisher[50];
    int available_copies;
    int categories[50];
    int issued_copies;
    int available_UID[50];
    int issued_UID[50];
} BOOK;

typedef struct category
{
    int no;
    char name[20];
} CAT;

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

int *generate_uid(BOOK *b, int *searchres)
{
    FILE *uniq;
    uniq = fopen("../BooksDB/UID.txt", "r+");
    int n, i, j;
    n = 0;
    if (!fread(&n, sizeof(int), 1, uniq))
    {
        printf("First Book Entered\n.");
        fwrite(&n, sizeof(int), 1, uniq);
    };
    printf("%d\n", n);
    for (i = 0; i < 50; i++)
    {
        if (b->available_UID[i] == 0)
            break;
    }
    for (j = i; j < b->available_copies; j++)
    {
        b->available_UID[j] = j + 1 + n;
    }
    n = n + b->available_copies - i;
    fseek(uniq, 0, 0);
    fwrite(&n, sizeof(int), 1, uniq);
    fclose(uniq);
}

int *search_result(BOOK b) // imitating the search function
{

    char *key = "Hello"; // search-key
    static int a[2];
    if (!strcmp(b.title, key))
    {
        a[0] = 1;
        a[1] = 32; // offset obtained by sizeof(BOOK)*number of times the search loop has run
    }
    return a;
}

int add_book()
{
    printf("You are in Add Book.\n");
}