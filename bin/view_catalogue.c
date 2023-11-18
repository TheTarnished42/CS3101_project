#include<string.h>
#include "../bin/structs.h"

void view_catalogue()
{
    system("clear");
    FILE *file=fopen("./BooksDB/books.txt", "r+");
    // printing all the books in the library
    BOOK b;
    printf("ISBN \tTITLE\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
    printf("=====\t=====\t\t\t======\t\t=========\t================\n");

    while(fread(&b, sizeof(BOOK), 1, file))
    {
     printf("%5s\t%-20s\t%-10s\t%-10s\t%04d\n",b.isbn,b.title,b.author,b.publisher,b.available_copies);
    }
    printf("\nPress Enter to continue.\n");
    getchar();
    getchar();
}