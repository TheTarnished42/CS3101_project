// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

// User defined modules
#include "./bin/login_menu.c"
#include "./bin/admin_menu.c"
#include "./bin/member_menu.c"
//#include "./bin/browse.c"
#include "./bin/add_book.c"
//#include "./bin/remove_book.c"
//#include "./bin/view_current_issue.c"
//#include "./bin/view_lib_log.c"
#include "./bin/add_user.c"
#include "./bin/request_issue.c"
//#include "./bin/submit_book.c"

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

        char *usertype = malloc(sizeof(char));
        char *password = malloc(100);
        char *userid = malloc(100);
        char *username = malloc(100);
        // Take ACTION from the user and checking if it is valid or not
        int *action = malloc(sizeof(int));

        // Take login info from the user and check wether the UID and PASSWORD is valid or not
        int flag_0 = 1;
        int flag_1 = 0;
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
                        printf("Login successful!\n");
                        printf("Welcome %s\n", username);
                        printf("You have logged in as a FACULTY.\n");
                        printf("Press Enter to Continue");
                        getchar();
                        flag_1 = 1;
                        break;
                }
        } while (flag_0 == 1);


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

        printf("USER-ID: %s, PASSWORD: %s, USERTYPE: %s, ACTION: %d\n", userid, password, usertype, *action);

        switch (*usertype)
        {
        case 'A':
        {
                switch (*action)
                {
                case 1:
                        printf("search_book");
                        //searchBook();
                        break;
                case 2:
                        getchar();
                        add_book();
                        break;
                case 3:
                        //remove_book();
                        printf("remove_book");
                        break;
                case 4:
                        printf("current issue view");
                        //view_current_issue();
                        break;
                case 5:
                        printf("view library log");
                        //view_lib_log();
                        break;
                case 6:
                        add_user();
                        break;
                                case 'S':
                        member_menu(action);
                        flag_1 = 0;
                        break;}
                break;
        }
        case 'S':
        {
                switch (*action)
                {
                case 1:
                        printf("browse_book");
                        //searchBook();
                        break;
                case 2:
                        submit_book(userid);
                        break;
                }
                break;
        }
        }
}