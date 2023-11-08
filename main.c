#include <stdio.h>
#include "./user_admin_ids/Check_id.c" // add other c files in this format
// command always returns back to main
void main()
{
    char id[10];
    // printf welcome format
    printf("Enter your ID: "); // NOTE THAT THIS ID MUST BE PASSED TO ISSUE files
    scanf("%s", id);
    // check_id etc.
    //  display options based on admin/user and initiate a call cascade as required.
}