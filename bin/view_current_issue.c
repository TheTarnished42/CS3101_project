#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"

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
    printf("|  User-ID  |\t");
    printf("|  Issue ISBN  |    ");
    printf("| Issue UID |\t");
    printf("| Issue period |    ");
    printf("|\t  Date of Issue\t     |");
    printf("\n|===========|\t|==============|    |===========|\t|==============|    |========================|\n");

    while (fread(&issue, sizeof(ISSUE), 1, fptr))
    {
        if (issue.copies_issued != 0)
        {
            // Assuming you want to print information about a single issue record

            for (int i = 0; i < issue.copies_issued; i++)
            {
                printf("  %-15s", issue.userid);
                // printf("Copies Issued: %d\n\n", issue.copies_issued);
                printf("   %-18s", issue.issued_isbn[i]);
                printf("  %-15s", issue.issued_UID[i]);
                printf("    %d days", issue.issue_period[i]);

                // Convert time_t to a readable string
                char *dateString = ctime(&issue.doi[i]);
                dateString[strlen(dateString) - 1] = '\0'; // Remove the newline character

                printf("\t     %s\n", dateString);
            }

            printf("\n");
        }
        printf(" ==============\n\n");
    }

    fclose(fptr);
    printf("\nEnter to continue.\n");
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
