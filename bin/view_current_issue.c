#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"

/*
typedef struct issue
{
    char userid[10];
    int copies_issued;
    char issued_UID[10][20];
    char issued_isbn[10][14];
    time_t doi[10];
} ISSUE;
*/
void view_current_issue()
{
    FILE *fptr;
    ISSUE issue;
    system("clear");
    printf("Current Issue\n");
    printf("========\n\n");

    fptr = fopen("./Issues/issues.txt", "rb");

    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    // Move the check outside the loop
    while (fread(&issue, sizeof(ISSUE), 1, fptr))
    {
        if (issue.copies_issued != 0)
        {
            // Assuming you want to print information about a single issue record
            printf("\nUser ID: %s\n", issue.userid);
            printf("Copies Issued: %d\n\n", issue.copies_issued);

            for (int i = 0; i < issue.copies_issued; i++)
            {
                printf("Issue UID: %s\n", issue.issued_UID[i]);
                printf("Issue ISBN: %s\n", issue.issued_isbn[i]);

                // Convert time_t to a readable string
                char *dateString = ctime(&issue.doi[i]);
                dateString[strlen(dateString) - 1] = '\0'; // Remove the newline character

                printf("DOI: %s\n\n", dateString);
            }

            printf("\n");
            
        }
        printf("========\n\n");
    }

    fclose(fptr);
    printf("Enter to continue.\n");
    getchar();
}

/*
int main()
{
    // Use this function to write sample data to the file
    // Comment it out once the file is created.
//    write_sample_data();

    view_current_issue();
    return 0;
}*/
