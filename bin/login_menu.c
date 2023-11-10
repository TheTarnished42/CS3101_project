/*
This code displays the login menu when you log in to the library
*/

void login_menu(int *usertype, char *uid, char *password)
{
    system("clear");
    printf("Login to Access the library\n");
    printf("Enter USER ID: ");
    scanf("%s",uid);
    //password= getpass("Enter PASSWORD: ");
    printf("Enter PASSWORD: ");
    scanf("%s",password);
    system("clear");

// insert the checking command to see wether the given password is correct or not
// decide the usertype accordingly and update accordingly give -1 for invalid combination
    printf("Enter 1 for Admin and 2 for Member: ");
    scanf("%d", usertype);
}