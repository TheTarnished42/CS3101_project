#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    int day;
    int month;
    int year;
} DATE;

typedef struct student //Defining the user struct 
{
    char student_id[5];
    char issued_id[3][5];  
    char book_title[3][50];  
    DATE date_of_issue[3];
} STUDENT;

struct book_result //Rough struct that I shall get after calling search
{
    char title[50];
    char author[50];
    char publisher[50];
    char bkid[5];
    int av_copies;
    int iss_copies;
};

void request_item(char *s_id)
{
    char sbook[50];  // Assuming book titles can be up to 50 characters long
    printf("You are in Request Issue\n\n");
    printf("Enter the book you want to issue: ");
    scanf("%s\n", sbook);

    //There shall be a call of browse function which I have immitated as rbook

    int j, temp1, count; //Defining some useful variables
    const char *filename = "hello.txt"; //txt file which has stored student struct
    struct book_result rbook; //rbook is the struct that I shall get after calling search_books.c

    strcpy(rbook.title, "Aishi's Galaxy"); //rough book title
    strcpy(rbook.author, "Someone"); //rough book author
    strcpy(rbook.publisher, "ABCD"); //rough publisher
    strcpy(rbook.bkid, "B092"); //rough book id
    rbook.av_copies = 5; //rough available copies of the book
    rbook.iss_copies = 1; //rough issued copies of the book

    FILE *fptr; //defines file pointer
    STUDENT stu; //defines struct in request_item
    fptr = fopen(filename, "r"); //opens file name
    temp1 = rbook.av_copies - rbook.iss_copies; //temp1 stores number of copies of the book that is not issued

    printf("Number of copies of the book available: %d\n", temp1);

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
    }
    while (fread(&stu, sizeof(STUDENT), 1, fptr)) //Reads file
    {
        if (strcmp(stu.student_id, s_id) == 0) //Finds out the required student id
        {
            count = 0; //'count' counts the number of books a student has issued
            for (j = 0; j<3; j++)
            {
                if (stu.issued_id[j][0] != '\0') //Checks which array items are non empty in stu.issued_id
                {
                    count++;
                }
            }
            if ((count<3) && (temp1>0)) //Checks if there are enough available books and also the student has issued less than 5 books
            {
                printf("You can issue the book '%s' from its %d available copies\n\n", rbook.title, temp1); 
            }
            else if (temp1==0)
            {
                printf("There are no available copies of the book you want to issue.\n");
            }
            else if (count==3)
            {
                printf("You've reached your maximum limit of issued books at 5.\n");
                printf("To borrow additional books, please ensure you return at least one from your issues.");
            }
            
        }
    }
    fclose(fptr);
    //Here book issue in book struct shall be modified
    //update_item(s_id, rbook.bkid, rbook.title); //For updating student issue struct
    //Next log shall be called
}

void main() //Checks if my above code makes sense
{
    char *id = "S123";
    request_item(id);
}