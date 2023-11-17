#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
void main()
{
    FILE *fptr, *catptr;
    BOOK book;
    CAT c;
    fptr = fopen("../BooksDB/books.txt", "r+");
    catptr = fopen("../BooksDB/Categories.txt", "r+");
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while (fread(&book, sizeof(BOOK), 1, fptr) && fread(&c, sizeof(CAT), 1, catptr)) {
        printf("Title = %s || Author = %s || Publisher = %s || Copies = %d || ", book.title, book.author, book.publisher, book.available_copies);

        // Print categories for the current book
        printf("Categories: ");
        for (int i = 0; i < 50; i++)
        {
            if (book.categories[i] != 0) {
                printf("%d ", book.categories[i]);
            }
            else
            {
                break;
            }
        }
        printf("\nCurrent Position: %u", ftell(fptr));
        printf("\n");
    }

    fclose(fptr);
    fclose(catptr);

}