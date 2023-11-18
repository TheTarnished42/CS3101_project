/*
This code displays the login menu when you log in to the library
*/
#include<stdio.h>
#include "./structs.h"
#include <string.h>
// #include <conio.h>   
#include <unistd.h>   

void login_menu(char *usertype, char *uid, char *password, char *username)
{
    system("clear");
    printf("\t\t\t   =============================================================\n");
    printf("\t\t\t   ||                                                         ||\n");
    printf("\t\t\t   ||               Welcome to GLitched Library               ||\n");
    printf("\t\t\t   ||                                                         ||\n");
    printf("\t\t\t   || Made with love by Ahan, Aishi, Apuroop, Nivas and Rohan ||\n");
    printf("\t\t\t   ||                                                         ||\n");
    printf("\t\t\t   =============================================================\n\n\n");
    printf("Login to Access the library\n");
    printf("Enter USER ID: ");
    scanf("%s",uid);
    //password= getpass("Enter PASSWORD: ");
    //printf("Enter PASSWORD: ");
    //scanf("%s",password);
    //system("clear");

// insert the checking command to see wether the given password is correct or not
// decide the usertype accordingly and update accordingly give -1 for invalid combination
    // printf("Enter 1 for Admin and 2 for Member: ");
    // scanf("%s", usertype);


    FILE *file=fopen("./BooksDB/user_id.txt", "r+");
    MEMBER m;

    int flag=0;

    while (fread(&m, sizeof(MEMBER), 1, file))
    {
        if (strcmp(uid, m.m_id) == 0)
        {   printf("Welcome %s!\n",m.first_name);

            while(flag==0){
            password= getpass("Enter PASSWORD: ");
            // printf("Enter PASSWORD: ");
            // scanf("%s",password);
            //scanf("%s",password);
            getchar();
            if (strcmp(password, m.m_psswd) == 0)
            {
                flag=1;
                *usertype=m.m_id[0];
                strcpy(username,m.first_name);
                //sscanf(username,"%s",m.first_name);
                break;
            }
            else{
                printf("Invalid Password!!\n");
                printf("Enter 0 to re-enter Password, 1 to continue.\n");
                scanf("%d",&flag);
            }
        }
        }
    }
}