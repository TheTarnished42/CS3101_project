#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

int *generate_uid(BOOK *b)
{
    FILE *uniq;
    uniq = fopen("../BooksDB/UID.txt", "r+");
    int n, i, j;
    fread(&n, sizeof(int), 1, uniq);

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

        printf("ISBN: ");
        scanf("%lld", &b1.isbn);

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
    FILE *booksptr;
    booksptr = fopen("../BooksDB/books.txt", "r+");
    search_result = searchBook(b1);
    printf("Returned Values: %d, %d\n", search_result[0], search_result[1]);
    if (search_result[0] == 1)
    {
        BOOK b2;
        fseek(booksptr, search_result[1], SEEK_SET);
        fread(&b2, sizeof(BOOK), 1, booksptr);
        b2.available_copies += b1.available_copies;
        printf("Records Updated.\n");
        fseek(booksptr, search_result[1], SEEK_SET); //Lines added by pro coder
        fwrite(&b2, sizeof(BOOK), 1, booksptr); //Lines added by pro coder
    }
    else
    {
        b1.issued_copies = 0;
        generate_uid(&b1); // 1 for new entry, 0 for old entry
        fseek(booksptr, 0, SEEK_END);
        fwrite(&b1, sizeof(BOOK), 1, booksptr);
        printf("New Entry Added.");
    }
    fclose(booksptr);
    return 0;
}
/*
void main()
{
    // system("clear");
    add_book();

    printf("\nExit\n");
    
}*/