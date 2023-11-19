#include <stdio.h>
#include <string.h>
#include <time.h>
#include "structs.h"

void view_issued_book(char u_id[10])
{
    printf("\n");
    int i, days_left;
    BOOK book;
    ISSUE us;
    FILE *issfile;
    FILE *bkfile;
    time_t now;
    time(&now);
    double period_d, period_s;
    issfile = fopen("./Issues/issues.txt", "r"); //"../Issues/issues.txt", "r+" need to use in main
    bkfile = fopen("./BooksDB/books.txt", "r");  //"../BooksDB/books.txt", "r+" need to use in main

    if (issfile == NULL || bkfile == NULL)
    {
        perror("Error opening files");
        return;
    }
    printf("%-6s\t%-8s\t%-20s\t%-15s\t%-20s\t%-24s\t%-11s\n", "ISBN", "BOOK ID", "TITLE", "AUTHOR", "PUBLISHER", "DATE OF ISSUE", "DAYS LEFT");
    printf("%-6s\t%-8s\t%-20s\t%-15s\t%-20s\t%-24s\t%-11s\n", "====", "=======", "=====", "======", "=========", "=============", "==========");

    while (fread(&us, sizeof(ISSUE), 1, issfile))
    {
        if (strcmp(us.userid, u_id) == 0)
        {
            while (fread(&book, sizeof(BOOK), 1, bkfile))
            {
                for (i = 0; i < 10; i++)
                {
                    if (strcmp(us.issued_isbn[i], book.isbn) == 0)
                    {
                        period_s = difftime(now, us.doi[i]);
                        period_d = period_s / 86400;
                        days_left = us.issue_period[i] - period_d;
                        char *doi_str = ctime(&us.doi[i]);
                        doi_str[strcspn(doi_str, "\n")] = '\0';
                        printf("%-6s\t%-8s\t%-20s\t%-15s\t%-20s\t%-24s\t%-11d\n", book.isbn, us.issued_UID[i], book.title, book.author, book.publisher, doi_str, days_left);
                    }
                }
            }
        }
    }
    fclose(issfile);
    fclose(bkfile);
    printf("\n");
    printf("Press Enter to Continue.");
    getchar();
}

// void main()
// {
//     printf("hello\n");
//     char user[10];
//     strcpy(user, "SNM00002");
//     printf("%s\n", user);
//     view_issued_book(user);
// }