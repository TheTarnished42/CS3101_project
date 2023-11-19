#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100


void displayLogEntries(const char *filename, int startLine, int numLines) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char line[MAX_LINE_LENGTH];

    // Find the total number of lines in the file
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }

    // Move the file pointer to the starting line
    rewind(file);
    int currentLine = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        currentLine++;

        // Display entries in reverse order (most recent first)
        if (currentLine > count - startLine - numLines && currentLine <= count - startLine) {
            printf("%s", line);
        }
    }

    fclose(file);
}

void view_lib_log() {
    int startLine = 0;
    int numLines = 10;
    char response;

    do {
        // Display log entries
        displayLogEntries("./Log/log.txt", startLine, numLines);

        // Ask user if they want to see the next set of entries
        printf("Do you want to see the next %d entries? (y/n): ", numLines);
        scanf(" %c", &response);

        // Update starting line for the next set of entries
        startLine += numLines;

    } while (response == 'y' || response == 'Y');

    
}

