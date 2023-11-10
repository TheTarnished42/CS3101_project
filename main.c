//Standard C libraries
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>

//User defined modules
#include "./user_admin_ids/Check_id.c"
#include "./bin/login_menu.c"
#include "./bin/admin_menu.c"
#include "./bin/member_menu.c"

// command always returns back to main
void main()
{
    system("clear");
    printf("=============================================================\n");
    printf("||                                                         ||\n");
    printf("||               Welcome to GLitched Library               ||\n");
    printf("||                                                         ||\n");
    printf("|| Made with love by Ahan, Aishi, Apuroop, Nivas and Rohan ||\n");
    printf("||                                                         ||\n");
    printf("=============================================================\n\n\n");

    printf("Press Enter to Continue");
    getchar();
    system("clear");

    int *usertype= malloc(sizeof(int));
    char *password= malloc(100);
    char *uid= malloc(100);

    int flag_0=1;
    int flag_1=0;
    do{
        login_menu(usertype, uid, password);

        switch(*usertype)
        {
            case 1: flag_0=0;
                    printf("Login successful!\n");
                    printf("Welcome %s\n",uid);
                    printf("You have logged in as an Admin.\n");
                    printf("Press Enter to Continue");
                    getchar();
                    getchar();
                    flag_1=1;
                    break;
            case 2: flag_0=0;
                    printf("Login successful!\n");
                    printf("Welcome %s\n",uid);
                    printf("You have logged in as a Member.\n");
                    printf("Press Enter to Continue");
                    getchar();
                    getchar();
                    flag_1=1;
                    break;
            default: system("clear");
                     printf("Invalid USERNAME or PASSWORD!\n");
                     printf("Enter 1 to re-enter, 0 to exit.\n");
                     scanf("%d",&flag_0);
                     break;
        }
    }while (flag_0==1);
    
    //printf("USER-ID: %s, PASSWORD: %s, USERTYPE: %d\n", uid, password, *usertype);
    int *action=malloc(sizeof(int));

    while(flag_1==1){
        switch(*usertype){
            case 1: admin_menu(action);
                    flag_1=0;
                    break;
            case 2: member_menu(action);
                    flag_1=0;
                    break;
            default: *action=-1;
                    break;
        }
        if (*action==-1){
            printf("Invalid action selected!\n");
            printf("Enter 1 to re-select the action, 0 to exit.\n");
            scanf("%d",&flag_1);
        }
    }

    printf("USER-ID: %s, PASSWORD: %s, USERTYPE: %d, ACTION: %d\n", uid, password, *usertype, *action);
//    printf("Enter 1 to select action again, 0 to continue.\n");

//}while (flag_1==1)

}