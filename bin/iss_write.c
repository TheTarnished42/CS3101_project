//This is the code to create a rough txt file "hello.txt" to be able to write the code for request_item, update_item and submit_book

#include <stdio.h>
#include <string.h>

typedef struct 
{
    int day;
    int month;
    int year;
} DATE;

typedef struct student
{
    char student_id[5];
    char issued_id[3][5];  
    char book_title[3][50];
    DATE date_of_issue[3];  
} STUDENT;

DATE date(int day, int month, int year) 
{
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
        specific_date.day = specific_date.month = specific_date.year = -1;
        return specific_date;
    }
}

void iss_write(const char *filename, STUDENT* stu, int n)
{
    FILE *fptr;
    int i;
    fptr = fopen(filename, "w");
    for (i = 0; i < n; i++)
    {
        fwrite(&stu[i], sizeof(STUDENT), 1, fptr);
    }
    fclose(fptr);
}

void iss_read(const char *filename)
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

void main()
{
    STUDENT students[2];
    char filename[] = "hello.txt";

    // Student 1
    strcpy(students[0].student_id, "S123");
    strcpy(students[0].issued_id[0], "B111");
    strcpy(students[0].issued_id[1], "B123");
    strcpy(students[0].book_title[0], "Let us C");
    strcpy(students[0].book_title[1], "Python Programming");
    students[0].date_of_issue[0] = date(11, 3, 2023);
    students[0].date_of_issue[1] = date(13, 4, 2023);

    // Student 2
    strcpy(students[1].student_id, "S456");  
    strcpy(students[1].issued_id[0], "B222");
    strcpy(students[1].issued_id[1], "B234");
    strcpy(students[1].book_title[0], "How to code");
    strcpy(students[1].book_title[1], "Programming Art");
    students[1].date_of_issue[0] = date(9, 3, 2023);
    students[1].date_of_issue[1] = date(14, 4, 2023);

    iss_write(filename, students, 2);
    iss_read(filename);
}
