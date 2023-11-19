#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void view_log() // log viewed
{
    FILE *file = fopen("./Log/log.txt", "rb");
    fseek(file, -sizeof(LogEntry), SEEK_END);
    if (file == NULL)
    {
        printf("Error opening log file!\n");
        return;
    }

    printf("TIMESTAMP\t\tUSERID\t\t\tACTION\n");
    printf("==========\t\t======\t\t\t======\n");

    LogEntry logEntry;
    char act[50];
    int counter = 0;
    while (fread(&logEntry, sizeof(LogEntry), 1, file))
    {
        switch (logEntry.userid[0])
        {
        case 'F':
            switch (logEntry.action)
            {
            case 1:
                strcpy(act, "Book Issued");
                break;
            case 2:
                strcpy(act, "Submitted Book");
                break;
            case 3:
                strcpy(act, "Viewed Catalogue");
                break;
            case 4:
                strcpy(act, "Viewed Current Issues");
                break;
            case 0:
                strcpy(act, "Logout");
                break;
            case -2:
                strcpy(act, "Login");
                break;
            default:
                strcpy(act, "Unknown Action");
                break;
            }
            break;
        case 'S':
            switch (logEntry.action)
            {
            case 1:
                strcpy(act, "Browsed");
                break;
            case 2:
                strcpy(act, "Submitted");
                break;
            case 3:
                strcpy(act, "Viewed Catalogue");
                break;
            case 4:
                strcpy(act, "Viewed Current Issues");
                break;
            case 0:
                strcpy(act, "Logout");
                break;
            case -2:
                strcpy(act, "Login");
                break;
            default:
                strcpy(act, "Unknown Action");
                break;
            }
            break;
        case 'A':
            switch (logEntry.action)
            {
            case 1:
                strcpy(act, "Book Added");
                break;
            case 2:
                strcpy(act, "Book Removed");
                break;
            case 3:
                strcpy(act, "Viewed current issued books");
                break;
            case 4:
                strcpy(act, "Viewed log");
                break;
            case 5:
                strcpy(act, "Added New User");
                break;
            case 6:
                strcpy(act, "Viewed Catalogue");
                break;
            case 7:
                strcpy(act, "Viewed user catalogue");
                break;
            case 0:
                strcpy(act, "Logout");
                break;
            case -2:
                strcpy(act, "Login");
                break;
            default:
                strcpy(act, "Unknown Action");
                break;
            }
            break;
        default:
            strcpy(act, "Unknown User");
            break;
        }

        printf("%-20s\t%-20s\t%s\n", logEntry.timestamp, logEntry.userid, act);
        fseek(file, -2 * sizeof(logEntry), SEEK_CUR);
        if (counter == 10)
            break;
        else
            counter++;
    }

    fclose(file);
    printf("\nLast 10 log entries printed.Press Enter to continue.\n");
    getchar(); // Wait for Enter key press
}

// int main()
// {
//     view_log();
//     return 0;
// }
