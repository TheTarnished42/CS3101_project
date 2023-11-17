
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "structs.h"
// #include "member_menu.c"

#define MAX_WORDS 50
#define MAX_WORD_LENGTH 50

int unique_index;
// int n;

int *searchBook(BOOK b)
{
    BOOK b1;
    int counter;
    static int arr[2];
    arr[0] = 0;
    arr[1] = 0;
    char *file = "../BooksDB/books.txt";
    FILE *fptr = fopen(file, "r+");
    printf("In SEARCH!!!!!!!\n\n");

    if (fptr == NULL)
    {
        printf("File not Found!");
        exit(1);
    }

    else
    {
        while (fread(&b1, sizeof(BOOK), 1, fptr))
        {
            if (b.isbn == b1.isbn)
            {
                printf("\nBooks already exists at position %ld!\n", ftell(fptr));
                arr[0] = 1;
                arr[1] = ftell(fptr) - sizeof(BOOK);
                break;
            }
        }
    }
    fclose(fptr);
    return arr;
}

long *searchByCategories()
{
    FILE *catptr = fopen("../BooksDB/Categories.txt", "r+");
    CAT c;
    system("clear");
    printf("----------EXISTING CATEGORIES----------\n\n");
    while (fread(&c, sizeof(c), 1, catptr))
    {
        printf("[%d] %s\n", c.no, c.name);
    }

    printf("\n\n----------xxxxxxxxxx----------\n\n");

    int cat[c.no];
    int count = 0;
    int num;
    int flag = 0;
    while (1)
    {
        while (1)
        {
            printf("\nEnter category number(s) (Enter 0 to stop): ");
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
        for (int i = 0; i < count; i++)
        {
            printf("%d ", cat[k]);
            k++;
        }
        printf("\n");
        printf("\nEnter 1 to confirm and 0 to re-enter your entries: ");
        int reenter;
        scanf("%d", &reenter);
        if (reenter == 1)
        {
            system("clear");
            break;
        }
        else
        {
            count = 0;
        }
    }

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
                printf("%s ", c.name);
            }
        }
    }
    printf("\n");

    long *arr_ftells = NULL;
    int max_elements = 10;
    arr_ftells = (long *)malloc(max_elements * sizeof(long));
    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
    BOOK b;
    int index = 0;
    while (fread(&b, sizeof(BOOK), 1, fptr))
    {
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                if (cat[i] == b.categories[j])
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

    unique_index = 0;
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

    // Print the elements of the array
    system("clear");
    printf("Elements of the array:\n\n");
    for (int i = 0; i < unique_index; i++)
    {
        printf("%ld ", arr_ftells[i]);
    }
    printf("\n");
    // Till here

    return arr_ftells;
}

int compare(char **str1, char **str2)
{
    int n, m;
    n = 0;
    m = 0;
    int count = 0;
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
    /*
        for (int i = 0; i < n; i++)
        {
            printf("%s,", words[i]);
        }
        printf("\n");*/
    return words;
}

long *searchByTitle(char str[100], int choice)
{

    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
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


    return ftell_arr;
}

long *searchByAuthor(char str[100], int choice)
{

    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
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


    return ftell_arr;
}

long *searchByPublisher(char str[100], int choice)
{

    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
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


    return ftell_arr;
}

long search()
{
    FILE *fptr = fopen("../BooksDB/books.txt", "r+");
    BOOK b;
    system("clear");
    printf("\nYou have chosen to search for a book.\n\n");
    printf("Enter '1' to search by category\n");
    printf("Enter '2' to search by name of the book\n");
    printf("Enter '3' to search by name of the author(s)\n");
    printf("Enter '4' to search by ISBN code of the book\n");
    printf("Enter '5' to go back to menu\n");
    int i;

    int choice;
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            long *result = searchByCategories();
            if (result == NULL)
            {
                printf("Error in search\n");
                return -1;
            }
            while (1)
            {
                printf("\nThe following books are available:\n==============================\n");

                for (i = 0; i < unique_index; i++)
                {
                    fseek(fptr, result[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    printf("\n[%d]: %s by %s; ISBN: %lld; No. of copies available: %d", (i + 1), b.title, b.author, b.isbn, b.available_copies);
                }
                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;

                while (1)
                {
                    printf("\nEnter the corresponding number of the book you want to issue: ");
                    scanf("%d", &ch);
                    if (ch < 0 || ch > result[i])
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                printf("result: %lu", result[ch - 1] - sizeof(BOOK));
                printf("You have chosen to issue this book:\n\n");
                fseek(fptr, result[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %lld; No. of copies available: %d\n", b.title, b.author, b.isbn, b.available_copies);
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

            return 1;
        case 2:
            char name_of_book[100];
            printf("\nEnter the name of the book: ");
            fgets(name_of_book, 100, stdin);
            name_of_book[strcspn(name_of_book, "\n")] = '\0';
            long *arr;
            arr = searchByTitle(name_of_book, 2);
            fseek(fptr, 0, SEEK_SET);
            for(i = 0; i < 100; i++)
            {
                if(arr[i] == -1)
                {
                    break;
                }
                printf("%d, ", arr[i]);
            }
            while (1)
            {
                printf("\nThe following books available\n==============================\n");

                for (i = 0; i < 100; i++)
                {
                    if (arr[i] == -1)
                    {
                        break;
                    }
                    fseek(fptr, arr[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    printf("\n[%d]: %s by %s; ISBN: %lld; No. of copies available: %d", (i + 1), b.title, b.author, b.isbn, b.available_copies);
                }
                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;
                printf("i: %d", i);
                while (1)
                {
                    printf("\nEnter the corresponding number of the book you want to issue: ");
                    scanf("%d", &ch);
                    if (ch < 0 || ch > i)
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                printf("You have chosen to issue this book:\n\n");
                fseek(fptr, arr[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %lld; No. of copies available: %d\n", b.title, b.author, b.isbn, b.available_copies);
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

        case 3:
            char name_of_auth[100];
            printf("\nEnter the name of the author: ");
            fgets(name_of_auth, 50, stdin);
            name_of_auth[strcspn(name_of_auth, "\n")] = '\0';
            long *arr2;
            arr2 = searchByAuthor(name_of_auth, 2);
            fseek(fptr, 0, SEEK_SET);
            
            while (1)
            {
                printf("\nThe following books available\n==============================\n");

                for (i = 0; i < 100; i++)
                {
                    if (arr2[i] == -1)
                    {
                        break;
                    }
                    fseek(fptr, arr2[i] - sizeof(BOOK), SEEK_SET);
                    fread(&b, sizeof(BOOK), 1, fptr);
                    printf("\n[%d]: %s by %s; ISBN: %lld; No. of copies available: %d", (i + 1), b.title, b.author, b.isbn, b.available_copies);
                }
                printf("\n\n");
                printf("\n\n==============================\n");
                int ch;
                printf("i: %d", i);
                while (1)
                {
                    printf("\nEnter the corresponding number of the book you want to issue: ");
                    scanf("%d", &ch);
                    if (ch < 0 || ch > i)
                    {
                        printf("Invalid Entry! Retry...");
                        continue;
                    }
                    break;
                }
                printf("You have chosen to issue this book:\n\n");
                fseek(fptr, arr2[ch - 1] - sizeof(BOOK), SEEK_SET);
                fread(&b, sizeof(BOOK), 1, fptr);
                printf("%s by %s; ISBN: %lld; No. of copies available: %d\n", b.title, b.author, b.isbn, b.available_copies);
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
            char isbn[100];

            printf("\nEnter the ISBN code of the book: ");
            fgets(isbn, 14, stdin);
            isbn[strcmp(isbn, "\n")] = '\0';
            // dataSearch(choice, isbn);
            return 1;

        case 5:
            return -1;
        default:
            system("clear");
            printf("Wrong choice! Enter again...\n\n");
            printf("Enter '1' to search by category\n");
            printf("Enter '2' to search by name of the book\n");
            printf("Enter '3' to search by name of the author(s)\n");
            printf("Enter '4' to search by ISBN code of the book\n");
            printf("Enter '5' to go back to menu\n");
        }
    }
}

void main()
{
    long result = search();
}
