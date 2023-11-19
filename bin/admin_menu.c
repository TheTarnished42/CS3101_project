/*
To displays the menu options available to the ADMIN
*/

void admin_menu(int *action) // admins menu interface
{
    system("clear");
    printf("You are in Library Menu!\n\n"); // printing options
    printf("Code\t\tAction\n");
    printf("====\t\t======\n");
    // printf("[1]\t\tBrowse\n");
    printf("[1]\t\tAdd Book\n");
    printf("[2]\t\tUpdate existing Book data\n");
    printf("[3]\t\tView Current Issue\n");
    printf("[4]\t\tView Library Log\n");
    printf("[5]\t\tAdd New USER\n");
    printf("[6]\t\tView Library Catalogue\n");
    printf("[7]\t\tView All Registered USERS\n");
    printf("[0]\t\tLOGOUT\n\n");
    printf("Enter code for the action: ");
    scanf("%d", action); // accepting user input
    getchar();
    // for invalid input
    if (*action != 1 && *action != 2 && *action != 3 && *action != 4 && *action != 5 && *action != 6 && *action != 7 && *action != 0)
    {
        *action = -1;
    }
}