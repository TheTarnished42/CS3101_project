#ifndef STRUCTS_H
#define STRUCTS_H
#include <time.h>

typedef struct book
{
    char title[100];
    char author[50];
    char publisher[50];
    int available_copies;
    int issued_copies;
    int categories[50];
    char isbn[14];
    char available_UID[50][10];
    char issued_UID[50][10];
} BOOK;

typedef struct member
{
    char m_id[20];
    char first_name[20];
    char last_name[20];
    char m_psswd[20];
    char type[2];

} MEMBER;

typedef struct category
{
    int no;
    char name[20];
} CAT;

typedef struct issue
{
    char userid[10];
    int copies_issued;
    char issued_UID[10][20];
    char issued_isbn[10][14];
    time_t doi[10];
} ISSUE;

#endif // STRUCTS_H