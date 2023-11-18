#include <string.h>
#include "../bin/structs.h"

void view_all_users()
{
    system("clear");  
    FILE *file = fopen("./BooksDB/user_id.txt", "r+");
    
    // printing all the books in the library
    MEMBER b;
    printf("USER-ID\t\tFIRST NAME\tLAST NAME\t\tPASSWORD\t\tDESIGNATION\n");
    printf("=======\t\t==========\t=========\t\t========\t\t===========\n");

    char desig[20];  // Declare desig as a character array

    while(fread(&b, sizeof(MEMBER), 1, file))
    {
        switch(b.type[0])  // Switch on a specific element of b.type
        {
            case 'F':
                strcpy(desig, "FACULTY");
                break;
            case 'S':
                strcpy(desig, "STUDENT");
                break;
            case 'A':
                strcpy(desig, "ADMIN");
                break;
            default:
                strcpy(desig, "UNKNOWN");
                break;
        }

        printf("%8s\t\t%10s\t%10s\t\t%10s\t\t%10s\n", b.m_id, b.first_name, b.last_name, b.m_psswd, desig);
    }
    printf("\nPress Enter to continue.\n");
    getchar();
}