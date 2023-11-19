#include <stdio.h>
#include <string.h>
#include "structs.h"
void print_byisbn(char isbn[14])
{
    BOOK b;
    FILE *bksptr;
    bksptr = fopen("./BooksDB/books.txt", "r");
    static int ctr = 1;
    while (fread(&b, sizeof(BOOK), 1, bksptr))
    {
        if (strcmp(isbn, b.isbn) == 0)
        {
            printf("%s", b.title);
            ctr++;
            break;
        }
    }
}
int issue_book(char *userid, char utype, long pos) // updatesbooks.txt and issues.txt
{

    BOOK b;
    ISSUE issue;
    FILE *issfile;
    FILE *bksfile;
    issfile = fopen("./Issues/issues.txt", "r+");
    bksfile = fopen("./BooksDB/books.txt", "r+");
    fseek(bksfile, pos, SEEK_SET);
    fread(&b, sizeof(BOOK), 1, bksfile);
    int issperiod;
    int flag = 0;

    if (b.available_copies == 0)
    {
        printf("No copies");
        getchar();
        return 0;
    }
    if (b.available_copies <= 3 && utype == 'S')
    {
        printf("Cannot be issued to student, less than 3 copies.\n");
        getchar();
        getchar();
        return 0;
    }
    else if (b.available_copies <= 3 && utype != 'S')
    {
        issperiod = 7;
        printf("This book's issue period is 7 days.\n");
    }
    else if (b.available_copies > 3 && b.available_copies <= 6)
    {
        issperiod = 15;
        printf("This book's issue period is 15 days.\n");
    }
    else if (b.available_copies > 6 && b.available_copies <= 10)
    {
        issperiod = 25;
        printf("This book's issue period is 25 days.\n");
    }
    else if (b.available_copies > 10)
    {
        issperiod = 30;
        printf("This book's issue period is 30 days.\n");
    }

    while (fread(&issue, sizeof(ISSUE), 1, issfile))
    {
        if (strcmp(issue.userid, userid) == 0)
        {
            // printf("User ISSUE struct exists\n");
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        // printf("New ISSUE struct\n");
        strcpy(issue.userid, userid);
        issue.copies_issued = 0;
        strcpy(issue.issued_UID[issue.copies_issued], b.available_UID[b.available_copies - 1]);
        time(&issue.doi[issue.copies_issued]);
        strcpy(issue.issued_isbn[issue.copies_issued], b.isbn);
        issue.issue_period[issue.copies_issued] = issperiod;
        issue.issue_period[issue.copies_issued + 1] = 0;
        // issue.doi[issue.copies_issued] += 1653;
        issue.copies_issued++;
        fwrite(&issue, sizeof(ISSUE), 1, issfile);
        fclose(issfile);
    }
    else if (flag == 1)
    {
        if (utype == 'S' && issue.copies_issued >= 3)
        {
            printf("MAX Issue limit reached, return a book first.\n");
            printf("Press Enter to continue.");
            getchar();
            return 0;
        }
        strcpy(issue.issued_UID[issue.copies_issued], b.available_UID[b.available_copies - 1]);
        time(&issue.doi[issue.copies_issued]);
        strcpy(issue.issued_isbn[issue.copies_issued], b.isbn);
        issue.issue_period[issue.copies_issued] = issperiod;
        issue.issue_period[issue.copies_issued + 1] = 0;
        // issue.doi[issue.copies_issued] += 1653;
        issue.copies_issued++;
        fseek(issfile, -sizeof(ISSUE), SEEK_CUR);
        fwrite(&issue, sizeof(ISSUE), 1, issfile);
        fclose(issfile);
        printf("Book Issued.\n");
    }

    // updating books.txt here:
    strcpy(b.issued_UID[b.issued_copies], b.available_UID[b.available_copies - 1]);
    strcpy(b.available_UID[b.available_copies - 1], "\0");
    b.available_copies--;
    b.issued_copies++;
    fseek(bksfile, -sizeof(BOOK), SEEK_CUR);
    fwrite(&b, sizeof(BOOK), 1, bksfile);
    printf("Library Database updated.\n");
    fclose(bksfile);
    printf("Enter to continue.");
    getchar();
    getchar();
}

int submit_book(char *userid)
{
    ISSUE issue;
    FILE *issfile;

    issfile = fopen("./Issues/issues.txt", "r+");
    int flag = 0;
    while (fread(&issue, sizeof(ISSUE), 1, issfile))
    {
        if (strcmp(issue.userid, userid) == 0)
        {
            // printf("User ISSUE struct exists\n");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("No book has been issued to you ever.\n");
        getchar();
        return 0;
    }

    int index = 0;
    if (issue.copies_issued == 0)
    {
        printf("No book issued to you.\n");
        getchar();
        return 0;
    }
    printf("You have the following books: (Enter 0 FOR BACK TO MENU)\n");

    for (int i = 0; i < issue.copies_issued; i++)
    {
        printf("[%d] ", (i + 1));
        print_byisbn(issue.issued_isbn[i]);
        printf("\n");
    }
    printf("\n Enter the Serial Number(listed above) of the book to be returned: ");
    scanf("%d", &index);
    getchar();
    if (index == 0)
    {
        // printf("Enter to Continue");
        // getchar();
        return 0;
    }

    index--;
    time_t now;
    time(&now);
    double period_s = difftime(now, issue.doi[index]);
    double period_d = period_s / 86400;
    printf("You had the book for %fs that is, %f days\n", period_s, period_d);
    printf("Issue Period was %d days.\n", issue.issue_period[index]);
    if (period_d >= issue.issue_period[index])
    {
        printf("Fine to be paid :Rs %f \n", (issue.issue_period[index] - period_d) * 10);
    }
    char uid[20], posisbn[14];
    strcpy(uid, issue.issued_UID[index]);
    strcpy(posisbn, issue.issued_isbn[index]);
    for (int i = index; i < issue.copies_issued; i++)
    {
        strcpy(issue.issued_UID[i], issue.issued_UID[i + 1]);
        strcpy(issue.issued_isbn[i], issue.issued_isbn[i + 1]);
        issue.issue_period[i] = issue.issue_period[i + 1];
        issue.doi[i] = issue.doi[i + 1];
    }
    // printf("flag1");
    issue.copies_issued--;
    fseek(issfile, -sizeof(ISSUE), SEEK_CUR);
    fwrite(&issue, sizeof(ISSUE), 1, issfile);
    fclose(issfile);
    // printf("Issues.txt updated.\n");

    BOOK b;
    FILE *bksfile;
    bksfile = fopen("./BooksDB/books.txt", "r+");
    while (fread(&b, sizeof(BOOK), 1, bksfile))
    {
        if (strcmp(b.isbn, posisbn) == 0)
        {
            int issued_UID_index = 0;
            while (strcmp(b.issued_UID[issued_UID_index], uid) != 0)
            {
                issued_UID_index++;
            }
            strcpy(b.available_UID[b.available_copies], b.issued_UID[issued_UID_index]);
            b.available_copies++;

            for (int i = issued_UID_index; i < b.issued_copies; i++)
            {
                strcpy(b.issued_UID[i], b.issued_UID[i + 1]);
            }
            b.issued_copies--;
            fseek(bksfile, -sizeof(BOOK), SEEK_CUR);
            fwrite(&b, sizeof(BOOK), 1, bksfile);
            fclose(bksfile);
            printf("\nBook submitted to the GLitched Library.\n");
            break;
        }
    }

    printf("Enter to continue.");
    getchar();
}
/*
void main()
{
    // issue_book("av21ms201", 'u', sizeof(BOOK));
    // submit_book("av21ms201");
    //  FILE *p;
    //  ISSUE is;
    //  p = fopen("../Issues/issues.txt", "r");
    //  fread(&is, sizeof(ISSUE), 1, p);
    //  // fread(&is, sizeof(ISSUE), 1, p);
    //  printf("%d\n", is.copies_issued);
    printf("Exit\n");
}*/