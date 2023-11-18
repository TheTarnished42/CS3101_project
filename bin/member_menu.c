/*
To displays the menu options available to the MEMBER
*/

void member_menu(int *action)
{
    system("clear");
    printf("Code\t\tAction\n");
    printf("====\t\t====\n");
    printf("[1]\t\tBrowse\n");
    printf("[2]\t\tSubmit Book\n");
    printf("[3]\t\tView Library Catalogue\n");
    printf("[0]\t\tEXIT TO HOME\n");
    printf("Enter code for the action: ");
    scanf("%d",action);
    if (*action!=1 && *action!=2 && *action!=3 && *action!=0)
        {
                *action=-1;
        }
}