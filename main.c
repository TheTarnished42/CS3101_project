// Standard C libraries
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

// User defined modules
#include "./bin/login_menu.c"
#include "./bin/admin_menu.c"
#include "./bin/member_menu.c"
#include "./bin/browse.c"
//#include "./bin/add_book.c"
#include "./bin/remove_book.c"
#include "./bin/view_current_issue.c"
#include "./bin/view_lib_log.c"
#include "./bin/add_user.c"
#include "./bin/request_item.c"
#include "./bin/submit_book.c"

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

        int *usertype = malloc(sizeof(int));
        char *password = malloc(100);
        char *uid = malloc(100);

        // Take login info from the user and check wether the UID and PASSWORD is valid or not
        int flag_0 = 1;
        int flag_1 = 0;
        do
        {
                login_menu(usertype, uid, password);

                switch (*usertype)
                {
                case 1:
                        flag_0 = 0;
                        printf("Login successful!\n");
                        printf("Welcome %s\n", uid);
                        printf("You have logged in as an Admin.\n");
                        printf("Press Enter to Continue");
                        getchar();
                        getchar();
                        flag_1 = 1;
                        break;
                case 2:
                        flag_0 = 0;
                        printf("Login successful!\n");
                        printf("Welcome %s\n", uid);
                        printf("You have logged in as a Member.\n");
                        printf("Press Enter to Continue");
                        getchar();
                        getchar();
                        flag_1 = 1;
                        break;
                default:
                        system("clear");
                        printf("Invalid USERNAME or PASSWORD!\n");
                        printf("Enter 1 to re-enter, 0 to exit.\n");
                        scanf("%d", &flag_0);
                        break;
                }
        } while (flag_0 == 1);

        // Take ACTION from the user and checking if it is valid or not
        int *action = malloc(sizeof(int));

        while (flag_1 == 1)
        {
                switch (*usertype)
                {
                case 1:
                        admin_menu(action);
                        flag_1 = 0;
                        break;
                case 2:
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

        printf("USER-ID: %s, PASSWORD: %s, USERTYPE: %d, ACTION: %d\n", uid, password, *usertype, *action);

        switch (*usertype)
        {
        case 1:
        {
                switch (*action)
                {
                case 1:
                        printf("search_book");
                        //searchBook();
                        break;
                case 2:
                        //add_book();
                        printf("add_book");
                        break;
                case 3:
                        remove_book();
                        break;
                case 4:
                        view_current_issue();
                        break;
                case 5:
                        view_lib_log();
                        break;
                case 6:
                        add_user();
                        break;
                }
                break;
        }
        case 2:
        {
                switch (*action)
                {
                case 1:
                        printf("search_book");
                        //searchBook();
                        break;
                case 2:
                        request_item();
                        break;
                case 3:
                        submit_book();
                        break;
                }
                break;
        }
        }
}