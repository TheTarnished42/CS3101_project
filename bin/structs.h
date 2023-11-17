#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct book
{
    char title[100];
    char author[50];
    char publisher[50];
    int available_copies;
    int issued_copies;
    int categories[50];
    long long isbn;
    int available_UID[50];
    int issued_UID[50];
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

#endif //STRUCTS_H