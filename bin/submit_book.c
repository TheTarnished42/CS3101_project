#include <stdio.h>
#include <string.h>

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

DATE date(int day, int month, int year) {
    DATE specific_date;
    if ((day > 0) && (day <= 31) && (month > 0) && (month <= 12)) 
    {
        specific_date.day = day;
        specific_date.month = month;
        specific_date.year = year;
        return specific_date;
    } 
    else 
    {
        specific_date.day = specific_date.month = specific_date.year = 0;
        return specific_date;
    }
}


void submit_book(char *s_id)
{
    char rbid[5]; 
    char *null = "";
    printf("You are in submit book\n");
    printf("Enter the ID of the book you want to return: ");
    scanf("%s", rbid);

    int i;
    const char *filename = "hello.txt"; //txt file which has stored student struct
    FILE *fptr; //defines file pointer
    STUDENT stud; //defines student struct 
    fptr = fopen(filename, "r+"); //opens file name

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
    }
    while (fread(&stud, sizeof(STUDENT), 1, fptr)) //Reads file
    {
        if (strcmp(stud.student_id, s_id) == 0) //Finds out the required student id
        {
            for (i=0; i<3; i++)
            {
                if (strcmp(stud.issued_id[i], rbid) == 0)
                {
                    strcpy(stud.issued_id[i], null); //Removes the issue id of the book to submit from issued_id array
                    strcpy(stud.book_title[i], null); //Removes the book title of the book to submit from book_title array
                    stud.date_of_issue[i] = date(0, 0, 0); //Removes the date of issue of the book to submit from date_of_issue array
                    fseek(fptr, -sizeof(STUDENT), 1);
                    fwrite(&stud, sizeof(STUDENT), 1, fptr); //Writes the updated struct to hello.txt    
                    break;  
                }
            }
            break;
        }
    }
    fclose(fptr);
}

void sub_read(const char *filename) //To print the student issue struct info so that file can be read and entries can be checked
{
    FILE *fptr;
    STUDENT stu;
    DATE specific_date;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error opening file %s for reading.\n", filename);
        return;
    }

    while (fread(&stu, sizeof(STUDENT), 1, fptr))
    {
        printf("Student ID: %s\n\n", stu.student_id);
        for (int i = 0; i < sizeof(stu.issued_id) / sizeof(stu.issued_id[0]); i++)
        {
            printf("Issued ID: %s\n", stu.issued_id[i]);
            printf("Book Title: %s\n", stu.book_title[i]);

            if (stu.date_of_issue[i].day != -1) 
            {
                printf("Date of issue: %02d-%02d-%d\n", stu.date_of_issue[i].day, stu.date_of_issue[i].month, stu.date_of_issue[i].year);
            } 
            else 
            {
                printf("Date of issue: Invalid date\n");
            }
            printf("\n");
        }
        printf("\n");
    }

    fclose(fptr);
}


void main() //Checks if my above code makes sense
{
    char filename[] = "hello.txt";
    char *id = "S456";
    submit_book(id);
    sub_read(filename);
}