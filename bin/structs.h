#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct book
{
    char title[100];
    char author[50];
    char publisher[50];
    int available_copies;
    int issued_copies;
    long long isbn;
    int available_UID[50];
    int issued_UID[50];
} BOOK;

#endif //STRUCTS_H