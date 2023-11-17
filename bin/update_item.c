#include <stdio.h>
#include <string.h>
#include <time.h>

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


DATE get_current_date() 
{
    DATE current_date;

    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    current_date.day = tm_info->tm_mday;
    current_date.month = tm_info->tm_mon + 1;  // Months are 0-based in tm struct
    current_date.year = tm_info->tm_year + 1900;  // Years since 1900 in tm struct

    return current_date;
}

void update_item(char *s_id, char *title, char *bkid)
{
    int i,j, temp1, count; //Defining some useful variables
    //int day = 30, month = 11, year = 2023;
    DATE dt = get_current_date();
    const char *filename = "hello.txt"; //txt file which has stored student struct
    FILE *fptr; //defines file pointer
    STUDENT st; //defines struct in update_item

    fptr = fopen(filename, "r+"); //opens file name
    if (fptr == NULL)
    {
        printf("Error opening file.\n");
    }
    while (fread(&st, sizeof(STUDENT), 1, fptr)) //Reads file
    {
        if (strcmp(st.student_id, s_id) == 0) //Finds out the required student id
        {
            for (i=0; i<3; i++)
            {
                if (st.issued_id[i][0] == '\0') //Checks which array item is empty in stu.issued_id
                {
                    strcpy(st.issued_id[i], bkid);//Updates currently issued book id
                    strcpy(st.book_title[i], title);//Updates currently issued book title
                    st.date_of_issue[i] = dt;
                    fseek(fptr, -sizeof(STUDENT), 1);
                    fwrite(&st, sizeof(STUDENT), 1, fptr); //Writes the updated struct to hello.txt
                    break;
                }
            }
            break;
        }
    }
    fclose(fptr);
}



void up_read(const char *filename) //To print the student issue struct info so that file can be read and entries can be checked
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
    char *t = "Aishi's Galaxy";
    char *id = "S456";
    char *bid = "B092";
    update_item(id, t, bid);
    up_read(filename);
}
