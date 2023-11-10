/*
To displays the menu options available to the ADMIN
*/

void admin_menu(int *action)
{
    system("clear");
    printf("Code\t\tAction\n");
    printf("====\t\t======\n");
    printf("[1]\t\tBrowse\n");
    printf("[2]\t\tAdd Book\n");
    printf("[3]\t\tRemove Book\n");
    printf("[4]\t\tView Current Issue\n");
    printf("[5]\t\tView Library Log\n");
    printf("[6]\t\tAdd New USER\n\n");
    printf("Enter code for the action: ");
    scanf("%d",action);
    if (*action!=1 && *action!=2 && *action!=3 && *action!=4 && *action!=5 && action!=6)
        {
                *action=-1;
        }
}