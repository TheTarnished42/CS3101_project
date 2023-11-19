#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"

int request_item(char *u_id, char utype, long pos)
{
    int issperiod;
    BOOK book;
    ISSUE us; 
    FILE *issfile;
    FILE *bkfile;

    issfile = fopen("../bin/issues.txt", "r+");
    bkfile = fopen("../bin/books.txt", "r+");
    fseek(bkfile, pos, SEEK_SET);
    fread(&book, sizeof(BOOK), 1, bkfile);

    int temp1 = book.available_copies;
    int flag = 0;
    printf("Number of copies of the book available: %d\n", temp1);

    //Request issue:

    while (fread(&us, sizeof(ISSUE), 1, issfile)) 
    {
        if (strcmp(us.userid, u_id) == 0) 
        {
            flag = 1;
            if (utype == 'u' && us.copies_issued >= 3)
            {
                printf("MAX Issue limit reached, <returns to main>\n");
                return 0;
            }
            else if (temp1==0)
            {
                printf("No copies available.\n");
                return 0;
            }
            else if (book.available_copies <= 3 && utype == 'u')
            {
                printf("Cannot be issued to student, less than 3copies");
                return 0;
            }
            else if (book.available_copies <= 3 && utype != 'u')
            {
                issperiod = 7;
                printf("You can issue this book for 7 days!\n");
            }
            else if (book.available_copies > 3 && book.available_copies <= 6)
            {
                issperiod = 15;
                printf("You can issue this book for 15 days!\n");
            }
            else if (book.available_copies > 6 && book.available_copies <= 10)
            {
                issperiod = 25;
                printf("You can issue this book for 25 days!\n");
            }
            else if (book.available_copies > 10)
            {
                issperiod = 30;
                printf("You can issue this book for 30 days!\n");
            }
            break;
        }
    }

    if (flag == 1)
    {
        strcpy(us.userid, u_id);
        us.copies_issued = 0;
        strcpy(us.issued_UID[0], book.available_UID[book.available_copies - 1]);
        strcpy(us.issued_isbn[0], book.isbn);
        time(&us.doi[0]);
        us.issue_period[0] = issperiod;
        fseek(issfile, -sizeof(ISSUE), SEEK_CUR);
        fwrite(&us, sizeof(ISSUE), 1, issfile);
        fclose(issfile);
    }

    //Update:
    int i;
    issfile = fopen("../bin/issues.txt", "r+"); 
    while (fread(&us, sizeof(ISSUE), 1, issfile)) 
    {
        if (strcmp(us.userid, u_id) == 0)
        {
            for (i=0; i<3; i++)
            {
                if (us.issued_UID[i][0] == '\0') 
                {
                    //Updating issue struct
                    strcpy(us.issued_UID[i], book.available_UID[book.available_copies - 1]);
                    strcpy(us.issued_isbn[i], book.isbn);
                    time(&us.doi[us.copies_issued]);
                    us.issue_period[i] = issperiod;
                    fseek(issfile, -sizeof(ISSUE), SEEK_CUR);
                    fwrite(&us, sizeof(ISSUE), 1, issfile); 
                    break;
                }
            }
            break;
        }
    }
    fclose(issfile);
    printf("Book issued successfully!\n");


    //Updaing book struct (Code unchanged)
    strcpy(book.issued_UID[book.issued_copies], book.available_UID[book.available_copies - 1]);
    strcpy(book.available_UID[book.available_copies - 1], "\0");
    book.available_copies--;
    book.issued_copies++;
    fseek(bkfile, -sizeof(BOOK), SEEK_CUR);
    fwrite(&book, sizeof(BOOK), 1, bkfile);
    fclose(bkfile);
    printf("Book file updated successfully!\n");

    return 0;

}

int submit_book(char *u_id)
{
    ISSUE us;
    FILE *issfile;
    int index, i, j;
    char *null = "";
    char rbid[20], isbn[14];
    issfile = fopen("../Issues/issues.txt", "r+");
    while (fread(&us, sizeof(ISSUE), 1, issfile)) 
    {
        if (strcmp(us.userid, u_id) == 0)
        {
            if (us.copies_issued == 0)
            {
                printf("No book issued to you.\n");
            }
            else
            {
                printf("You have the following books issued (Enter 0 FOR BACK TO MENU):\n");
                for (int i = 0; i < us.copies_issued; i++)
                {
                    printf("[%d] %s\n", (i + 1), us.issued_isbn[i]);
                }

                printf("\n Enter the Serial No. of the book to be returned: ");
                scanf("%d", &index);
                getchar();
                if (index == 0)
                return 0;

                index--;
                time_t now;
                time(&now);
                double period_s = difftime(now, us.doi[index]);
                double period_d = period_s / 86400;
                printf("You had the book for %fs that is, %f days\n", period_s, period_d);
                printf("Issue Period was %d days.\n", us.issue_period[index]);
                if (period_d >= us.issue_period[index])
                {
                    printf("Fine to be paid :Rs %f \n", (us.issue_period[index] - period_d) * 10);
                }

                strcpy(rbid, us.issued_UID[index]);
                strcpy(isbn, us.issued_isbn[index]);

                for (j=0; j<3; j++)
                {
                    if (strcmp(us.issued_UID[j], rbid) == 0)
                    {
                        strcpy(us.issued_UID[i], null);
                        strcpy(us.issued_isbn[i], null); 
                        us.issue_period[i] = '\0';
                        fseek(issfile, -sizeof(ISSUE), 1);
                        fwrite(&us, sizeof(ISSUE), 1, issfile); 
                        break;  
                    }
                }
                break;

            }
        }
    }
    fclose(issfile);

    //Updating book databse (Code unchanged)
    BOOK b;
    FILE *bksfile;
    bksfile = fopen("../BooksDB/books.txt", "r+");
    while (fread(&b, sizeof(BOOK), 1, bksfile))
    {
        if (strcmp(b.isbn, isbn) == 0)
        {
            int issued_UID_index = 0;
            while (strcmp(b.issued_UID[issued_UID_index], rbid) != 0)
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
            printf("Book submitted successfully!\n");
            break;
        }
    }

}

void main()
{
    char *id = "SNM00002";
    char type = 'u';
    long p = 1424; 
    request_item(id, type, p);
}
