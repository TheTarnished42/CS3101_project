#include <stdio.h>
#include <string.h>
typedef struct member
{
    char m_id[20];
    char first_name[20];
    char last_name[20];
    char m_psswd[20];
    char type[2];

} MEMBER;

void main()
{
    MEMBER m;
    strcpy(m.m_id, "ARK00000");
    strcpy(m.first_name, "Rohan");
    strcpy(m.last_name, "Kumar");
    strcpy(m.m_psswd, "rohan");
    strcpy(m.type, "A");
    FILE *f;
    f = fopen("./BooksDB/user_id.txt", "r+");
    fwrite(&m, sizeof(MEMBER), 1, f);
}