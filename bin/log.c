#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"

void libraryLog(char *userid, int action)
{
    FILE *logFile;
    time_t rawtime;
    struct tm *timeinfo;

    // Open the library log file in append mode
    logFile = fopen("./Log/log.txt", "ab");

    if (logFile == NULL)
    {
        printf("Error opening log file!\n");
        exit(1);
    }

    // Get the current time
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Create a LogEntry structure and populate it with data
    LogEntry logEntry;
    strftime(logEntry.timestamp, sizeof(logEntry.timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    snprintf(logEntry.userid, sizeof(logEntry.userid), "%s", userid);
    logEntry.action = action;

    // Write the log entry to the library log file using fwrite
    if (fwrite(&logEntry, sizeof(LogEntry), 1, logFile) != 1)
    {
        printf("Error writing to log file!\n");
    }

    // Close the library log file
    fclose(logFile);
}

// int main()
// {

// }
