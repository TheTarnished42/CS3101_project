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
void writeToLogFile(const char *filename, const char *userid, const char *bookid, const char *action) {
    FILE *file = fopen(filename, "a"); // Open file in append mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char timestamp[20];
    getTimestamp(timestamp);

    // Write headings if the file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "\tTimestamp\t\tUserID\t\tBookID\t\tAction\n");
    }

    // Write data to file with two-tab separation
    fprintf(file, "%s\t\t%s\t\t%s\t\t%s\n", timestamp,		userid,		bookid, 	action);

    fclose(file);
}

int main() {
    char userid[50];
    char bookid[50];
    char action[10];

    // Get user input
    printf("Enter UserID: ");
    scanf("%s", userid);

    printf("Enter BookID: ");
    scanf("%s", bookid);

    printf("Enter Action (add, issue, remove, submit): ");
    scanf("%s", action);

    // Write data to file
    writeToLogFile("/home/nivasmummadi/CS3101_project/BooksDB/log.txt", userid, bookid, action);

    printf("Data written to log.txt successfully.\n");

    return 0;
}

