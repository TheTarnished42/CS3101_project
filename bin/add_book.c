#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <ctype.h>
// #include "./cmn_fxns_book.c"
//  #include "./browse.c"
//  void print_categories(BOOK b)
//  {
//      FILE *catptr;
//      CAT c;
//      catptr = fopen("./BooksDB/Categories.txt", "r+");
//      int i = 0;
//      printf("--Categories--\n");
//      while (b.categories[i] != 0)
//      {
//          while (fread(&c, sizeof(CAT), 1, catptr))
//          {
//              if (c.no == b.categories[i])
//                  printf("%s\n", c.name);
//          }
//          i++;
//          fseek(catptr, 0, SEEK_SET);
//      }
//      printf("\n");
//      fclose(catptr);
//  }

int uid_and_overwrite(BOOK *b, int *searchres, char *userid) // generates uid and adds book to database
{
    BOOK b2;
    FILE *uniq; // opens issue ptr
    int n = 0;
    uniq = fopen("./BooksDB/books.txt", "r+"); // opens database file
    while (fread(&b2, sizeof(BOOK), 1, uniq))  // reads database for counting purpose
    {
        n++;
    }
    if (searchres[0] == 1) // if the book already existed
    {
        printf("Stock Of Book increased.\n"); // stock is increased
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
        for (int i = 0; i < b->available_copies; i++) // uid generated
        {
            sprintf(uid, "%d.%d", n2, (i + 1 + total_copies));
            strcpy(b2.available_UID[i2 + i], uid);
        }
        b2.available_copies += b->available_copies; // updated
        // strcpy(b2.available_UID[total_copies + b->available_copies], '\0');
        fseek(uniq, -sizeof(BOOK), SEEK_CUR); // written
        fwrite(&b2, sizeof(BOOK), 1, uniq);
    }
    else
    {
        printf("New Book ADDED.\n"); // for new books not present in database
        char uid[10];
        fseek(uniq, 0, SEEK_END); // adding at end
        for (int i = 1; i <= b->available_copies; i++)
        {
            sprintf(uid, "%d.%d", (n + 1), i); // generating uid
            strcpy(b->available_UID[i - 1], uid);
        }
        // strcpy(b->available_UID[b->available_copies], "\0");
        b->issued_copies = 0;
        // strcpy(b->issued_UID[0], '\0');
        fwrite(b, sizeof(BOOK), 1, uniq);
    }
    libraryLog(userid, 1);
    fclose(uniq);
    printf("Press Enter to Continue");
}

int add_book(char *userid) // THIS FUNCTION IS USED TO ADD BOOK BY ADMIN
{
    printf("You are in Add Book.\n");
    BOOK b1;
    // b1 is the input structure.
    int flag_input = 0;
    int *search_result;

    do // loop is done to make multiple attempts
    {  // input
        printf("ISBN(5-digits): ");
        fgets(b1.isbn, 14, stdin);
        b1.isbn[strcspn(b1.isbn, "\n")] = '\0';

        search_result = searchBook(b1.isbn); // checks if the book already exists
        if (search_result[0] == 1)           // book already exists
        {
            char yn;
            // printf("Book Already Exists!");
            printf("Is this the Book whose stock is to be increased? [y/n]: ");
            scanf("%c", &yn);
            getchar();
            if (tolower(yn) == 'y')
            {
                printf("Number of new copies to be added: "); // accepting number of copies to be added
                scanf("%d", &b1.available_copies);
                getchar();
                break; // breaks the loop and goes to update database directly.
            }
            else
            {
                printf("Enter ISBN again.\n"); // reenter
                continue;
            }
        }
        printf("Enter the Book details:\nTitle: "); // logic follows here if the previous isbn doesnot exist
        fgets(b1.title, 100, stdin);                // fgets used to accept strings with space
        b1.title[strcspn(b1.title, "\n")] = '\0';   // removing newline character to not cause errors when comparing

        printf("Author: ");
        fgets(b1.author, 50, stdin);
        b1.author[strcspn(b1.author, "\n")] = '\0';

        printf("Publisher: ");
        fgets(b1.publisher, 50, stdin);
        b1.publisher[strcspn(b1.publisher, "\n")] = '\0';

        input_categories(&b1); // input categories is called here, used to assign categories to the book.

        printf("Number of Copies: ");
        scanf("%d", &b1.available_copies);

        while (1)
        {
            printf("\nConfirm Input[1] , Re-enter[2] or back-to-menu[0]?: "); // confirming input
            int cnfm;
            scanf("%d", &cnfm);
            if (cnfm == 0)
                return 0;
            else if (cnfm == 2)
            {
                printf("\n---RE_ENTRY---\n");
                break;
            }
            else if (cnfm == 1)
            {
                printf("Input Confirmed.\n");
                flag_input++;
                break;
            }
            else
                printf("Invalid input, Choose again.\n");
        }
        getchar();
    } while (flag_input == 0);
    // Input Complete. Now we update the books.txt file.

    // printf("Returned Values: %d, %d\n", search_result[0], search_result[1]);
    uid_and_overwrite(&b1, search_result, userid); // generates unique id for each copy
    getchar();
    return 0;
}

// commented out code for running file individually.
/*
void main()
{
    // add_book();
    //  FILE *fptr;
    //  BOOK b1;
    //  fptr = fopen("../BooksDB/books.txt", "r+");
    //  fread(&b1, sizeof(BOOK), 1, fptr);
    //  // fread(&b1, sizeof(BOOK), 1, fptr);
    //  printf("%s\n", b1.title);
    //  printf("%d", b1.available_copies);
    // printf("\nExit\n");
}*/