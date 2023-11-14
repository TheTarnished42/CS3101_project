#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
/*
// Function to compare two strings ignoring case
int compareIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (toupper(*str1) != toupper(*str2))
        {
            return 0; // Not equal
        }
        str1++;
        str2++;
    }
    
    // Check if both strings have reached the end simultaneously
    return (*str1 == '\0' && *str2 == '\0');
}
*/

int *searchBook(BOOK b)
{
    BOOK b1;
    int counter;
    static int arr[2];
    arr[0] = 0;
    arr[1] = 0;
    char *file = "../BooksDB/books.txt";
    FILE *fptr = fopen(file, "r+");
    printf("In SEARCH!!!!!!!\n\n");

    if (fptr == NULL)
    {
        printf("File not Found!");
        exit(1);
    }

    else
    {
        while (fread(&b1, sizeof(BOOK), 1, fptr))
        {
            if(b.isbn == b1.isbn)
            {
                printf("\nBooks already exists at position %ld!\n", ftell(fptr));
                arr[0] = 1;
                arr[1] = ftell(fptr) - sizeof(BOOK);
                break;
            }
        }
    }
    fclose(fptr);
    return arr;
}