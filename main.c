// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

// User defined modules
#include "./bin/login_menu.c"
#include "./bin/admin_menu.c"
#include "./bin/member_menu.c"
#include "./bin/browse.c"
#include "./bin/add_book.c"
#include "./bin/remove_book.c"
#include "./bin/view_current_issue.c"
//#include "./bin/view_lib_log.c"
#include "./bin/add_user.c"
#include "./bin/request_issue.c"
#include "./bin/view_catalogue.c"
#include "./bin/view_all_user.c"
#include "./bin/view_lib_log.c"
#include "./bin/log.c"
//#include <string.h>

//#include "./bin/submit_book.c"

int main()

{
do{
/*
        printf("Press Enter to Continue");
        getchar();
        system("clear");
*/
        char *usertype = malloc(sizeof(char));
        char *password = malloc(20);
        char *userid = malloc(20);
        char *username = malloc(20);
        // Take ACTION from the user and checking if it is valid or not
        int *action = malloc(sizeof(int));

        // Take login info from the user and check wether the UID and PASSWORD is valid or not
        int flag_0 = 1;
        int flag_1 = 0;
        int flag_3=1;
        do
        {
                login_menu(usertype, userid, password, username);

                switch (*usertype)
                {
                case 'A':
                        flag_0 = 0;
                        system("clear");
                        printf("Login successful!\n");
                        printf("Welcome %s\n", username);
                        printf("You have logged in as an ADMIN.\n");
                        printf("Press Enter to Continue");
                        getchar();
                        flag_1 = 1;
                        break;
                case 'S':
                        flag_0 = 0;
                        system("clear");
                        printf("Login successful!\n");
                        printf("Welcome %s\n", username);
                        printf("You have logged in as a STUDENT.\n");
                        printf("Press Enter to Continue");
                        getchar();
                        flag_1 = 1;
                        break;
                case 'F':
                        flag_0 = 0;
                        system("clear");
                        printf("Login successful!\n");
                        printf("Welcome %s\n", username);
                        printf("You have logged in as a FACULTY.\n");
                        printf("Press Enter to Continue");
                        getchar();
                        flag_1 = 1;
                        break;
                }
        } while (flag_0 == 1);

do{
        while (flag_1 == 1)
        {
                switch (*usertype)
                {
                case 'A':
                        admin_menu(action);
                        flag_1 = 0;
                        break;
                case 'S':
                        member_menu(action);
                        flag_1 = 0;
                        break;
                case 'F':
                        member_menu(action);
                        flag_1 = 0;
                        break;
                default:
                        *action = -1;
                        break;
                }
                if (*action == -1)
                {
                        printf("Invalid action selected!\n");
                        printf("Enter 1 to re-select the action, 0 to exit.\n");
                        scanf("%d", &flag_1);
                }
        }

        //printf("USER-ID: %s, PASSWORD: %s, USERTYPE: %s, ACTION: %d\n", userid, password, usertype, *action);

        switch (*usertype)
        {
        case 'A':
        {
                switch (*action)
                {
                case 1:
                        add_book();
                        break;
                case 2:
                        remove_book();
                        break;
                case 3:
                        view_current_issue();
                        break;
                case 4:
                        //printf("view library log");
                        view_lib_log();
                        break;
                case 5:
                        add_user();
                        break;
                case 6:
                        view_catalogue();
                        break;
                case 7:
                        view_all_users();
                        break;
                case 0:
                        flag_3=0;
                        break;
                        }

                //getchar();
                break;
        }
        case 'S':
        {
                switch (*action)
                {
                case 1:
                        //printf("browse_book");
                        long pos=search();
                        if (pos!=-1)
                        {
                            printf("Position of book is %ld",pos);
                            issue_book(userid, *usertype, pos);
                        }
                            break;
                case 2:
                        getchar();
                        submit_book(userid);
                        break;
                case 3: 
                        getchar();
                        view_catalogue();
                        break;
                case 0:
                        flag_3=0;
                        break;
                }
                break;
        }
        case 'F':
        {
                switch (*action)
                {
                case 1:
                        long pos=search();
                        if (pos!=-1)
                        {
                            printf("Position of book is %ld",pos);
                            issue_book(userid, *usertype, pos);
                        }
                        break;
                case 2:
                        printf("submit_book");
                        getchar();
                        submit_book(userid);
                        break;
                case 3: 
                        getchar();
                        view_catalogue();
                        break;
                case 0:
                        flag_3=0;
                        break;
                }
                break;
        }
        }
        flag_1=1;
        writeToLogFile(userid, *action);
}while(flag_3==1);
}while(1);
}