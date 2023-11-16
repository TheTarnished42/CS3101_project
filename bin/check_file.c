#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
void main()
{
    FILE *fptr;
    BOOK book;
    fptr = fopen("../BooksDB/books.txt", "r+");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while (fread(&book, sizeof(BOOK), 1, fptr))
    {
        printf("Title = %s Author = %s Publisher = %s Number of Copies = %d\n", book.title, book.author, book.publisher, book.available_copies);
        printf("Current position: %ld \n", ftell(fptr));
    }
    fclose(fptr);
}