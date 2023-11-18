#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to get current timestamp
void getTimestamp(char *timestamp) {
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", info);
}

// Function to write data to file with headings
void writeToLogFile(char *userid, int action) {
    FILE *file = fopen("./Log/log.txt", "a"); // Open file in append mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char timestamp[20];
    getTimestamp(timestamp);

    // Write headings if the file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "\tTimestamp\tUserID\tAction\n");
    }

    // Write data to file with two-tab separation
    fprintf(file, "%s\t%s\t%d\n", timestamp,		userid, 	action);

    fclose(file);
}