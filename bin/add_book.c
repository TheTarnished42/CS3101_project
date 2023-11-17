#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
// #include "./browse.c"

int *searchBook(BOOK b)
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
        if (b.isbn == b1.isbn)
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

int uid_and_overwrite(BOOK *b, int *searchres)
{
    BOOK b2;
    FILE *uniq;
    int n = 0;
    uniq = fopen("../BooksDB/UID.txt", "r+");
    while (fread(&b2, sizeof(BOOK), 1, uniq))
    {
        n++;
    }
    if (searchres[0] == 1)
    {
        fseek(uniq, searchres[1], SEEK_SET);
        fread(&b2, sizeof(BOOK), 1, uniq);
    }
    else
    {
        char uid[10];
        fseek(uniq, 0, SEEK_END);
        for (int i = 1; i <= b->available_copies; i++)
        {
            sprintf(uid, "%d.%d", (n + 1), i);
            strcpy(b->available_UID[i - 1], uid);
        }
        fwrite(&b, sizeof(BOOK), 1, uniq);
    }
    // int n, i, j;
    // fread(&n, sizeof(int), 1, uniq);

    // for (i = 0; i < 50; i++)
    // {
    //     if (b->available_UID[i] == 0)
    //         break;
    // }
    // for (j = i; j < b->available_copies; j++)
    // {
    //     b->available_UID[j] = j + 1 + n;
    // }
    // n = n + b->available_copies - i;
    // fseek(uniq, 0, 0);
    // fwrite(&n, sizeof(int), 1, uniq);
    // fclose(uniq);
}

int add_book()
{
    printf("You are in Add Book.\n");
    BOOK b1;
    // b1 is the input structure.
    int flag_input = 0;
    do
    { // input
        printf("Enter the Book details:\nTitle: ");
        fgets(b1.title, 100, stdin);
        b1.title[strcspn(b1.title, "\n")] = '\0';

        printf("Author: ");
        fgets(b1.author, 50, stdin);
        b1.author[strcspn(b1.author, "\n")] = '\0';

        printf("Publisher: ");
        fgets(b1.publisher, 50, stdin);
        b1.publisher[strcspn(b1.publisher, "\n")] = '\0';

        printf("ISBN(5-digits): ");
        fgets(b1.isbn, 14, stdin);
        b1.title[strcspn(b1.title, "\n")] = '\0';

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
    int *search_result;
    search_result = searchBook(b1);
    printf("Returned Values: %d, %d\n", search_result[0], search_result[1]);
    uid_and_overwrite(&b1, search_result);
    return 0;
}

void main()
{
    system("clear");
    add_book();

    printf("\nExit\n");
}
