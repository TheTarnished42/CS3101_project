#include <stdio.h>
#include <string.h>
#include "struct.h"
void iss_read(const char *filename)
{
    FILE *fptr;
    ISSUE stu;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file %s for reading.\n", filename);
        return;
    }

    while (fread(&stu, sizeof(ISSUE), 1, fptr))
    {
        printf("Student ID: %s\n\n", stu.userid);
        for (int i = 0; i < sizeof(stu.issued_isbn) / sizeof(stu.issued_isbn[0]); i++)
        {
            printf("Issued ISBN: %s\n", stu.issued_isbn[i]);
            printf("\n");
        }
        printf("\n");
    }

    fclose(fptr);
}

void main()
{
    char *issfile= "issues.txt";
    char *bkfile = "books.txt";
    iss_read(issfile);
    iss_read(bkfile);
}