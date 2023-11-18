#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "structs.h"

#define MAX_WORDS 50
#define MAX_WORD_LENGTH 50
#define BOOKS_PER_PAGE 10

int unique_index;

/*
searchByCategories() will take input from the user as to what
categories he/she wants to enter and it returns an array of long integers containing
the positions of the BOOK structs in the file "books.txt"
*/
long *searchByCategories()
{
    FILE *catptr = fopen("./BooksDB/Categories.txt", "r+");
    CAT c;
    system("clear");

    int cat[50];
    int count = 0;
    int num;
    int flag = 0;

    while (1)
    {
        fseek(catptr, 0, SEEK_SET);

        // Printing existing categories
        printf("----------EXISTING CATEGORIES----------\n\n");
        while (fread(&c, sizeof(c), 1, catptr))
        {
            printf("[%d] %s\n", c.no, c.name);
        }

        printf("\n\n----------xxxxxxxxxx----------\n\n");

        // Accepting categories from user
        printf("\nEnter category number(s) (Enter 0 to stop):\n");
        while (1)
        {

            scanf("%d", &num);
            if (num == 0)
            {
                break;
            }
            if (num > c.no || num < 0)
            {
                printf("\nInvalid entry. Re-enter this entry...\n");
                continue;
            }
            for (int i = 0; i < count; i++)
            {
                if (cat[i] == num)
                {
                    printf("\nYou have already entered this category...\n");
                    flag = 1;
                }
            }
            if (flag == 1)
            {
                flag = 0;
                continue;
            }
            cat[count] = num;
            count++;
        }

        int k = 0;

        printf("\n--------------------\n");
        printf("\nPrinting categories entered: ");
        // Printing the categories entered
        for (int i = 0; i < count; i++)
        {
            printf("%d ", cat[i]);
        }
        printf("\n");

        // Seeking for confirmation
        printf("\nEnter [1] to confirm and [0] to re-enter your entries: ");
        int reenter;
        scanf("%d", &reenter);
        if (reenter == 1)
        {
            system("clear");
            break;
        }
        else
        {
            system("clear");
            count = 0;
        }
    }

    // Printing the categories entered
    system("clear");
    printf("====================");
    printf("\nCategories confirmed: ");

    int k = 0;

    for (int i = 0; i < count; i++)
    {
        fseek(catptr, 0, SEEK_SET);
        while (fread(&c, sizeof(c), 1, catptr))
        {
            if (c.no == cat[k])
            {
                printf("%s, ", c.name);
                k++;
            }
        }
    }
    printf("\n");

    // Declaring a pointer element to store all the ftell(fptr) values of the books
    // belonging to the entered categories
    long *arr_ftells = NULL;
    int max_elements = 10;
    arr_ftells = (long *)malloc(max_elements * sizeof(long));
    FILE *fptr = fopen("./BooksDB/books.txt", "r+");
    BOOK b;
    int index = 0;
    k = 0;
    int l = 0;
    // Assigning values to arr_ftells
    while (fread(&b, sizeof(BOOK), 1, fptr))
    {
        for (int i = 0; i < 50; i++)
        {
            if (b.categories[i] == 0)
            {
                break;
            }
            else
            {
                for (int j = 0; j < count; j++)
                {
                    if (b.categories[i] == cat[j])
                    {

                        if (index >= max_elements)
                        {

                            max_elements *= 2;
                            arr_ftells = (long *)realloc(arr_ftells, max_elements * sizeof(long));
                        }

                        arr_ftells[index] = ftell(fptr);
                        index++;
                    }
                }
            }
        }
    }

    unique_index = 0;
    // Removing duplicates
    for (int i = 0; i < index; i++)
    {
        int duplicate = 0;
        for (int j = 0; j < unique_index; j++)
        {
            if (arr_ftells[i] == arr_ftells[j])
            {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate)
        {
            arr_ftells[unique_index] = arr_ftells[i];
            unique_index++;
        }
    }

    arr_ftells = (long *)realloc(arr_ftells, unique_index * sizeof(long));

    return arr_ftells;
}
/*
compare(char**, char**) takes as input an array of words and
returns the number of words common
*/
int compare(char **str1, char **str2)
{
    int n, m;
    n = 0;
    m = 0;
    int count = 0; //Counter variable to store the number of words in common
    while (str1[n] != NULL)
    {
        m = 0;
        while (str2[m] != NULL)
        {
            if (strcmp(str1[n], str2[m]) == 0)
            {
                count++;
            }
            m++;
        }
        n++;
    }
    return count;
}

/*
tokenize(char[]) takes a string as input and returns a double-pointer
thereby tokenizing the entire string into an array of words separated
by white space
*/
char **tokenize(char str[100])
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }

    char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
    for (int i = 0; i < MAX_WORDS; i++)
    {
        words[i] = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
    }

    char *token = strtok(str, " ");
    int n = 0;

    while (token != NULL)
    {
        words[n] = strdup(token);
        n++;
        token = strtok(NULL, " ");
    }

    words[n] = NULL;
    return words;
}
/*
searchByTitle() will take input from the user as to what
title he/she wants to enter and it returns an array of long integers containing
the positions of the BOOK structs in the file "books.txt"

This array is sorted such that it allows free text search by the user in the title
of the book
*/
long *searchByTitle(char str[100])
{

    FILE *fptr = fopen("./BooksDB/books.txt", "r+");
    BOOK b;

    int arr[100];
    long *ftell_arr = (long *)malloc(100 * sizeof(long));

    int result = 0;
    int index = 0;
    char **words1;
    char **words2;
    words1 = tokenize(str);
    while (fread(&b, sizeof(BOOK), 1, fptr))
    {
        words2 = tokenize(b.title);
        result = compare(words1, words2);
        if (result > 0)
        {
            arr[index] = result;
            ftell_arr[index] = ftell(fptr);
            index++;
        }

        for (int i = 0; words2[i] != NULL; i++)
        {
            free(words2[i]);
        }
        free(words2);
    }
    arr[index] = 0;
    ftell_arr[index] = -1;
    index++;

    for (int i = 0; words1[i] != NULL; i++)
    {
        free(words1[i]);
    }
    free(words1);

    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                long tempp = ftell_arr[j];
                ftell_arr[j] = ftell_arr[j + 1];
                ftell_arr[j + 1] = tempp;
            }
        }
    }
    unique_index = index;
    return ftell_arr;
}

long *searchByAuthor(char str[100])
{

    FILE *fptr = fopen("./BooksDB/books.txt", "r+");
    BOOK b;

    int arr[100];
    long *ftell_arr = (long *)malloc(100 * sizeof(long));

    int result = 0;
    int index = 0;
    char **words1;
    char **words2;
    words1 = tokenize(str);
    while (fread(&b, sizeof(BOOK), 1, fptr))
    {
        words2 = tokenize(b.author);
        result = compare(words1, words2);
        if (result > 0)
        {
            arr[index] = result;
            ftell_arr[index] = ftell(fptr);
            index++;
        }

        for (int i = 0; words2[i] != NULL; i++)
        {
            free(words2[i]);
        }
        free(words2);
    }
    arr[index] = 0;
    ftell_arr[index] = -1;
    index++;

    for (int i = 0; words1[i] != NULL; i++)
    {
        free(words1[i]);
    }
    free(words1);

    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                long tempp = ftell_arr[j];
                ftell_arr[j] = ftell_arr[j + 1];
                ftell_arr[j + 1] = tempp;
            }
        }
    }
    unique_index = index;
    return ftell_arr;
}

long *searchByPublisher(char str[100])
{

    FILE *fptr = fopen("./BooksDB/books.txt", "r+");
    BOOK b;

    int arr[100];
    long *ftell_arr = (long *)malloc(100 * sizeof(long));

    int result = 0;
    int index = 0;
    char **words1;
    char **words2;
    words1 = tokenize(str);
    while (fread(&b, sizeof(BOOK), 1, fptr))
    {
        words2 = tokenize(b.publisher);
        result = compare(words1, words2);
        if (result > 0)
        {
            arr[index] = result;
            ftell_arr[index] = ftell(fptr);
            index++;
        }

        for (int i = 0; words2[i] != NULL; i++)
        {
            free(words2[i]);
        }
        free(words2);
    }
    arr[index] = 0;
    ftell_arr[index] = -1;
    index++;

    for (int i = 0; words1[i] != NULL; i++)
    {
        free(words1[i]);
    }
    free(words1);

    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                long tempp = ftell_arr[j];
                ftell_arr[j] = ftell_arr[j + 1];
                ftell_arr[j + 1] = tempp;
            }
        }
    }
    unique_index = index;
    return ftell_arr;
}

long *searchByFreeText(char str[100])
{
    FILE *fptr = fopen("./BooksDB/books.txt", "r+");
    BOOK b;

    int arr[100];
    long *ftell_arr = (long *)malloc(100 * sizeof(long));

    int result = 0;
    int index = 0;
    char **words1;
    char **words2;
    words1 = tokenize(str);
    while (fread(&b, sizeof(BOOK), 1, fptr))
    {
        char str2[100];
        strcpy(str2, b.title);
        strcat(str2, " ");
        strcat(str2, b.author);
        strcat(str2, " ");
        strcat(str2, b.publisher);
        words2 = tokenize(str2);
        result = compare(words1, words2);
        if (result > 0)
        {
            arr[index] = result;
            ftell_arr[index] = ftell(fptr);
            index++;
        }

        for (int i = 0; words2[i] != NULL; i++)
        {
            free(words2[i]);
        }
        free(words2);
    }
    arr[index] = 0;
    ftell_arr[index] = -1;
    index++;

    for (int i = 0; words1[i] != NULL; i++)
    {
        free(words1[i]);
    }
    free(words1);

    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                long tempp = ftell_arr[j];
                ftell_arr[j] = ftell_arr[j + 1];
                ftell_arr[j + 1] = tempp;
            }
        }
    }
    unique_index = index;
    return ftell_arr;
}
long search()
{
    FILE *fptr = fopen("./BooksDB/books.txt", "r+");
    BOOK b;

user_entered_zero:
    system("clear");
    printf("\nYou have chosen to search for a book.\n\n");
    printf("Enter the appropriate code\n\n");
    printf("[1] to search by category\n");
    printf("[2] to search by name of the book\n");
    printf("[3] to search by name of the author(s)\n");
    printf("[4] to search by name of the publisher(s)\n");
    printf("[5] to search by ISBN code of the book\n");
    printf("[6] for free text search\n");
    printf("[7] to go back to menu\n");
    int i;
    int page = 1;
    int totalBooks = 0;

    int choice;
    while (1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
        reenter_cat:
            page = 1;
            totalBooks = 0;
            long *result = searchByCategories();
            if (result == NULL)
            {
                printf("Error in search\n");
                return -1;
            }
        pageupdate_1:
            while (1)
            {
                int startIdx = (page - 1) * BOOKS_PER_PAGE;
                int endIdx = startIdx + BOOKS_PER_PAGE;

                printf("\nThe following books are available:\n==============================\n");
                printf("S.No.\tISBN \tTITLE\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
                printf("=====\t=====\t=====\t\t\t======\t\t=========\t================\n");
                for (i = startIdx; i < endIdx && i < unique_index; i++)
                {
                    fseek(fptr, result[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    printf("[%d]\t%5s\t%-20s\t%-10s\t%-10s\t%04d\n", (i + 1), b.isbn, b.title, b.author, b.publisher, b.available_copies);
                    totalBooks++;
                }
                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;

                char ch2;
            one:
                printf("\nUse '>' for the next page, '<' for the previous page, '0' to continue: ");
                scanf(" %c", &ch2);
                getchar();
                switch (ch2)
                {
                case '>':
                    if (endIdx < unique_index)
                    {
                        page++;
                    }
                    system("clear");
                    goto pageupdate_1;
                    break;
                case '<':
                    if (page > 1)
                    {
                        page--;
                    }
                    system("clear");
                    goto pageupdate_1;
                    break;
                case '0':
                    break;
                default:
                    printf("\nInvalid entry! Retry...\n");
                    goto one;
                    break;
                }
                printf("\n--------------------\n(Enter [0] to re-enter categories and [-1] to return to menu)\n--------------------\n");
                while (1)
                {
                    printf("\nEnter the Serial No. of the book you want to issue:");
                    scanf("%d", &ch);
                    if (ch < -1 || ch > unique_index)
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                if (ch == 0)
                {
                    goto reenter_cat;
                }
                if (ch == -1)
                {
                    goto user_entered_zero;
                }

                printf("\nYou have chosen to issue this book:\n\n");
                fseek(fptr, result[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %s; No. of copies available: %d\n\n", b.title, b.author, b.isbn, b.available_copies);
            invalid_1:
                printf("\n--------------------\nEnter [1] to confirm and [0] to reselect: ");
                int cc;
                scanf("%d", &cc);

                if (cc == 1)
                {

                    return ftell(fptr) - sizeof(BOOK);
                }
                else if (cc == 0)
                {
                    system("clear");
                    continue;
                }
                else
                {
                    printf("\nInvalid Input...\n");
                    goto invalid_1;
                }
            }

            return 1;
        case 2:
            char name_of_book[100];
        reenter_title:
            printf("\nEnter the name of the book: ");
            fgets(name_of_book, 100, stdin);
            name_of_book[strcspn(name_of_book, "\n")] = '\0';
            long *arr;
            arr = searchByTitle(name_of_book);
            fseek(fptr, 0, SEEK_SET);

            totalBooks = 0;
            page = 1;
        pageupdate_2:
            while (1)
            {

                int startIdx = (page - 1) * BOOKS_PER_PAGE;
                int endIdx = startIdx + BOOKS_PER_PAGE;

                printf("\nThe following books available (displayed in decreasing order of similarity to your search query):\n==============================\n");
                printf("S.No.\tISBN \tTITLE\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
                printf("=====\t=====\t=====\t\t\t======\t\t=========\t================\n");
                for (i = 0; i < endIdx && i < unique_index; i++)
                {
                    if (arr[i] == -1)
                    {
                        break;
                    }
                    fseek(fptr, arr[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    totalBooks++;
                    printf("[%d]\t%5s\t%-20s\t%-10s\t%-10s\t%04d\n", (i + 1), b.isbn, b.title, b.author, b.publisher, b.available_copies);
                }
                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;

                char ch2;
            two:
                printf("\nUse '>' for the next page, '<' for the previous page, '0' to continue: ");
                scanf(" %c", &ch2);
                getchar();
                switch (ch2)
                {
                case '>':
                    if (endIdx < unique_index)
                    {
                        page++;
                    }
                    system("clear");
                    goto pageupdate_2;
                    break;
                case '<':
                    if (page > 1)
                    {
                        page--;
                    }
                    system("clear");
                    goto pageupdate_2;
                    break;
                case '0':
                    break;
                default:
                    printf("\nInvalid entry! Retry...\n");
                    goto two;
                    break;
                }
                printf("\n--------------------\n(Enter [0] to re-enter categories and [-1] to return to menu)\n--------------------\n");
                while (1)
                {
                    printf("\nEnter the Serial No. of the book you want to issue: ");
                    scanf("%d", &ch);
                    if (ch < -1 || ch > i)
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                if (ch == 0)
                {
                    system("clear");
                    getchar();
                    goto reenter_title;
                }
                if (ch == -1)
                {
                    system("clear");
                    getchar();
                    goto user_entered_zero;
                }
                printf("\nYou have chosen to issue this book:\n\n");
                fseek(fptr, arr[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %s; No. of copies available: %d\n", b.title, b.author, b.isbn, b.available_copies);
                printf("\nEnter [1] to confirm and [0] to reselect: ");
                int cc;
                scanf("%d", &cc);
                if (cc == 1)
                {

                    return ftell(fptr) - sizeof(BOOK);
                    break;
                }
                continue;
            }

        case 3:
            char name_of_auth[100];
        reenter_auth:
            printf("\nEnter the name of the author: ");
            fgets(name_of_auth, 50, stdin);
            name_of_auth[strcspn(name_of_auth, "\n")] = '\0';
            long *arr2;
            arr2 = searchByAuthor(name_of_auth);
            fseek(fptr, 0, SEEK_SET);
            page = 1;
            totalBooks = 0;
        pageupdate_3:

            while (1)
            {
                int startIdx = (page - 1) * BOOKS_PER_PAGE;
                int endIdx = startIdx + BOOKS_PER_PAGE;
                printf("\nThe following books available (displayed in decreasing order of similarity to your search query):\n==============================\n");
                printf("S.No.\tISBN \tTITLE\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
                printf("=====\t=====\t=====\t\t\t======\t\t=========\t================\n");
                for (i = startIdx; i < endIdx && i < unique_index; i++)
                {
                    if (arr2[i] == -1)
                    {
                        break;
                    }
                    fseek(fptr, arr2[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    totalBooks++;
                    printf("[%d]\t%5s\t%-20s\t%-10s\t%-10s\t%04d\n", (i + 1), b.isbn, b.title, b.author, b.publisher, b.available_copies);
                }
                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;
                char ch2;
            three:
                printf("\nUse '>' for the next page, '<' for the previous page, '0' to continue: ");
                scanf(" %c", &ch2);
                getchar();
                switch (ch2)
                {
                case '>':
                    if (endIdx < unique_index)
                    {
                        page++;
                    }
                    system("clear");
                    goto pageupdate_3;
                    break;
                case '<':
                    if (page > 1)
                    {
                        page--;
                    }
                    system("clear");
                    goto pageupdate_3;
                    break;
                case '0':
                    break;
                default:
                    printf("\nInvalid entry! Retry...\n");
                    goto three;
                    break;
                }
                printf("\n--------------------\n(Enter [0] to re-enter categories and [-1] to return to menu)\n--------------------\n");
                while (1)
                {
                    printf("\nEnter the Serial No. of the book you want to issue: ");
                    scanf("%d", &ch);
                    if (ch < -1 || ch > i)
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                if (ch == 0)
                {
                    system("clear");
                    getchar();
                    goto reenter_auth;
                }
                if (ch == -1)
                {
                    system("clear");
                    getchar();
                    goto user_entered_zero;
                }
                printf("\nYou have chosen to issue this book:\n\n");
                fseek(fptr, arr2[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %s; No. of copies available: %d\n", b.title, b.author, b.isbn, b.available_copies);
                printf("Enter [1] to confirm and [0] to reselect: ");
                int cc;
                scanf("%d", &cc);
                if (cc == 1)
                {

                    return ftell(fptr) - sizeof(BOOK);
                    break;
                }

                continue;
            }
        case 4:
            char name_of_pub[100];
        reenter_pub:
            printf("\nEnter the name of the publisher: ");
            fgets(name_of_pub, 50, stdin);
            name_of_pub[strcspn(name_of_pub, "\n")] = '\0';
            long *arr3;
            arr3 = searchByPublisher(name_of_pub);
            fseek(fptr, 0, SEEK_SET);
            page = 1;
            totalBooks = 0;

        pageupdate_4:
            while (1)
            {
                int startIdx = (page - 1) * BOOKS_PER_PAGE;
                int endIdx = startIdx + BOOKS_PER_PAGE;

                printf("\nThe following books available (displayed in decreasing order of similarity to your search query):5\n==============================\n");
                printf("S.No.\tISBN \tTITLE\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
                printf("=====\t=====\t=====\t\t\t======\t\t=========\t================\n");
                for (i = startIdx; i < endIdx && i < unique_index; i++)
                {
                    if (arr3[i] == -1)
                    {
                        break;
                    }
                    fseek(fptr, arr3[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    totalBooks++;
                    printf("[%d]\t%5s\t%-20s\t%-10s\t%-10s\t%04d\n", (i + 1), b.isbn, b.title, b.author, b.publisher, b.available_copies);
                }

                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;
                char ch2;
            four:
                printf("\nUse '>' for the next page, '<' for the previous page, '0' to continue: ");
                scanf(" %c", &ch2);
                getchar();
                switch (ch2)
                {
                case '>':
                    if (endIdx < unique_index)
                    {
                        page++;
                    }
                    system("clear");
                    goto pageupdate_4;
                    break;
                case '<':
                    if (page > 1)
                    {
                        page--;
                    }
                    system("clear");
                    goto pageupdate_4;
                    break;
                case '0':
                    break;
                default:
                    printf("\nInvalid entry! Retry...\n");
                    goto four;
                    break;
                }
                printf("\n--------------------\n(Enter [0] to re-enter categories and [-1] to return to menu)\n--------------------\n");
                while (1)
                {
                    printf("\nEnter the Serial No. of the book you want to issue: ");
                    scanf("%d", &ch);
                    if (ch < -1 || ch > i)
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                if (ch == 0)
                {
                    system("clear");
                    getchar();
                    goto reenter_pub;
                }
                if (ch == -1)
                {
                    system("clear");
                    getchar();
                    goto user_entered_zero;
                }

                printf("\nYou have chosen to issue this book:\n\n");
                fseek(fptr, arr3[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %s; No. of copies available: %d\n", b.title, b.author, b.isbn, b.available_copies);
                printf("Enter [1] to confirm and [0] to reselect: ");
                int cc;
                scanf("%d", &cc);
                if (cc == 1)
                {
                    return ftell(fptr) - sizeof(BOOK);
                    break;
                }

                continue;
            }

        case 5:
            char isbn[14];
        reenter_isbn:
            printf("\nEnter the ISBN code of the book: ");
            fgets(isbn, 14, stdin);
            isbn[strcspn(isbn, "\n")] = '\0';
            fseek(fptr, 0, SEEK_SET);
            int f = 0;
            printf("\n==============================\n\n");
            while (fread(&b, sizeof(BOOK), 1, fptr))
            {
                if (strcmp(isbn, b.isbn) == 0)
                {
                    f = 1;
                    printf("You have chosen to issue this book:\n\n");
                    printf("S.No.\tISBN \tTITLE\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
                    printf("=====\t=====\t=====\t\t\t======\t\t=========\t================\n");
                    printf("[%d]\t%5s\t%-20s\t%-10s\t%-10s\t%04d\n", (i + 1), b.isbn, b.title, b.author, b.publisher, b.available_copies);
                    printf("\nEnter [1] to confirm and [0] to re-enter ISBN: ");
                    int cc;
                    scanf("%d", &cc);
                    if (cc == 1)
                    {
                        return ftell(fptr) - sizeof(BOOK);
                        break;
                    }
                    if (cc == 0)
                    {
                        system("clear");
                        getchar();
                        goto reenter_isbn;
                    }
                }
            }
            if (f == 0)
            {
                printf("No such ISBN found! Enter [0] to re-enter ISBN and [-1] to return back to menu: ");
                int cc;
                scanf("%d", &cc);
                if (cc == 0)
                {
                    system("clear");
                    getchar();
                    goto reenter_isbn;
                }
                else if (cc == -1)
                {
                    system("clear");
                    getchar();
                    goto user_entered_zero;
                }
            }

        case 6:
            char query[100];
        reenter_query:
            printf("\nEnter your query: ");
            fgets(query, 100, stdin);
            query[strcspn(query, "\n")] = '\0';
            long *arr4;
            arr4 = searchByFreeText(query);
            fseek(fptr, 0, SEEK_SET);
            page = 1;
            totalBooks = 0;

        pageupdate_6:
            while (1)
            {
                int startIdx = (page - 1) * BOOKS_PER_PAGE;
                int endIdx = startIdx + BOOKS_PER_PAGE;

                printf("\nThe following books available (displayed in decreasing order of similarity to your search query):5\n==============================\n");
                printf("S.No.\tISBN \tTITLE\t\t\tAUTHOR\t\tPUBLISHER\tAVAILABLE COPIES\n");
                printf("=====\t=====\t=====\t\t\t======\t\t=========\t================\n");

                for (i = startIdx; i < endIdx && i < unique_index; i++)
                {
                    if (arr4[i] == -1)
                    {
                        break;
                    }
                    fseek(fptr, arr4[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    totalBooks++;
                    printf("[%d]\t%5s\t%-20s\t%-10s\t%-10s\t%04d\n", (i + 1), b.isbn, b.title, b.author, b.publisher, b.available_copies);
                }

                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;
                char ch2;
            six:
                printf("\nUse '>' for the next page, '<' for the previous page, '0' to continue: ");
                scanf(" %c", &ch2);
                getchar();
                switch (ch2)
                {
                case '>':
                    if (endIdx < unique_index)
                    {
                        page++;
                    }
                    system("clear");
                    goto pageupdate_6;
                    break;
                case '<':
                    if (page > 1)
                    {
                        page--;
                    }
                    system("clear");
                    goto pageupdate_6;
                    break;
                case '0':
                    break;
                default:
                    printf("\nInvalid entry! Retry...\n");
                    goto six;
                    break;
                }
                printf("\n--------------------\n(Enter [0] to re-enter categories and [-1] to return to menu)\n--------------------\n");
                while (1)
                {
                    printf("\nEnter the Serial No. of the book you want to issue: ");
                    scanf("%d", &ch);
                    if (ch < -1 || ch > i)
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                if (ch == 0)
                {
                    system("clear");
                    getchar();
                    goto reenter_query;
                }
                if (ch == -1)
                {
                    system("clear");
                    getchar();
                    goto user_entered_zero;
                }

                printf("\nYou have chosen to issue this book:\n\n");
                fseek(fptr, arr4[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %s; No. of copies available: %d\n", b.title, b.author, b.isbn, b.available_copies);
                printf("Enter [1] to confirm and [0] to reselect: ");
                int cc;
                scanf("%d", &cc);
                if (cc == 1)
                {
                    return ftell(fptr) - sizeof(BOOK);
                    break;
                }

                continue;
            }
        case 7:
            return -1;

        default:
            system("clear");
            printf("Wrong choice! Enter again...\n\n");
            printf("Enter '1' to search by category\n");
            printf("Enter '2' to search by name of the book\n");
            printf("Enter '3' to search by name of the author(s)\n");
            printf("Enter '4' to search by name of the publisher(s)\n");
            printf("Enter '5' to search by ISBN code of the book\n");
            printf("Enter '6' for free text search\n");
            printf("Enter '7' to go back to menu\n");
        }
    }
}