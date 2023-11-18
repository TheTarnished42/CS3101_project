#include <stdio.h>
#include "../bin/structs.h"
#include <ctype.h>

void add_user() {
    
    int flag=0;
    do{
        system("clear");
        printf("You are in ADD USER.\n");

    	FILE *file = fopen("./BooksDB/user_id.txt", "r+");

        MEMBER user;
    
        printf("Enter USER FIRST NAME\n");
        scanf("%s", user.first_name);

        printf("Enter USER LAST NAME\n");
        scanf("%s", user.last_name);

        printf("Enter USER TYPE (A,S,F)\n");
        scanf("%s", user.type);

        int n;
        fseek(file, 0, SEEK_END);
        n=(int)ftell(file)/sizeof(MEMBER);
        sprintf(user.m_id, "%c%c%c%05d",toupper(user.type[0]),toupper(user.first_name[0]),toupper(user.last_name[0]),n);
        printf("\nGenerated USER ID: %s\n",user.m_id);

        printf("Enter USER PASSWORD\n");
        scanf("%s", user.m_psswd);

        getchar();
        fseek(file, 0, SEEK_END);
        fwrite(&user,sizeof(MEMBER),1,file);
        fclose(file);

        printf("User registration successful. Data written to ./BooksDB/user_data.txt.\n");
        printf("Enter 1 to register new another USER, 0 to exit.\n");
        scanf("%d",&flag);
    }while(flag==1);
}