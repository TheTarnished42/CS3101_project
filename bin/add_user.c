#include <stdio.h>

// Define a struct for user information
struct User
{
    char fname[50];
    char sname[50];
    char post[50];
    char password[50];
    int userNumber; // A user-specific number
};

// Function to extract the serial number from the user ID
int extractSerialNumber(const char *userId)
{
    int serialNumber;
    sscanf(userId + 6, "%d", &serialNumber);
    return serialNumber;
}

int main()
{

    FILE *file = fopen("../user_admin_ids/user_data.txt", "a+");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    // Create a struct variable to store user information
    struct User user;

    // Move the file pointer to the end to read the last user ID
    fseek(file, 0, SEEK_END);

    // Check if the file is not empty
    if (ftell(file) != 0)
    {
        // Move the file pointer to the beginning
        fseek(file, 0, SEEK_SET);

        // Read the last user ID to get the serial number
        fscanf(file, "User ID: %*s\n"); // Skip "User ID: "
        char lastUserId[13];
        fscanf(file, "%s", lastUserId);
        user.userNumber = extractSerialNumber(lastUserId) + 1;
    }
    else
    {

        user.userNumber = 1;
    }

    printf("Enter your first name: ");
    scanf("%s", user.fname);

    printf("Enter your surname: ");
    scanf("%s", user.sname);

    printf("Enter your designation: ");
    scanf("%s", user.post);

    printf("Enter the password: ");
    scanf("%s", user.password);

    fprintf(file, "User ID: %s%s%04d\n", user.fname, user.sname, user.userNumber);
    fprintf(file, "First Name: %s\n", user.fname);
    fprintf(file, "Surname: %s\n", user.sname);
    fprintf(file, "Designation: %s\n", user.post);
    fprintf(file, "Password: %s \n", user.password);
    fprintf(file, "\n");

    fclose(file);

    printf("User registration successful. Data written to user_data.txt.\n");

    return 0;
}
