#include <string.h>
#include "../bin/structs.h"
#include <ctype.h>
void view_catalogue()
{
    system("clear");
    FILE *file = fopen("./BooksDB/books.txt", "r+");
    // printing all the books in the library
    BOOK b;
    printf("ISBN \tTITLE\t\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
    printf("=====\t=====\t\t\t\t======\t\t=========\t================\n");
    int counter = 0;
    while (fread(&b, sizeof(BOOK), 1, file))
    {
        printf("%5s\t%-25.25s\t%10.10s\t%9.9s\t%04d\n", b.isbn, b.title, b.author, b.publisher, b.available_copies); // formatted printing
        counter++;
        if (counter % 10 == 0) // printing only 10 entries at once
        {
            char yn;
            printf("Look at next the 10 books? [y/n]: ");
            scanf("%c", &yn);
            getchar();
            if (tolower(yn) == 'y')
            {
                printf("\n");
                continue;
            }
            else
            {
                break;
            }
        }
    }
    printf("\nPress Enter to continue.\n");
    getchar();
}