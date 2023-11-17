#include <stdio.h>
#include <string.h>
void main()
{
    char s[6];
    printf("ENter 5digits: ");
    fgets(s, 6, stdin);
    s[strcspn(s, "\n")] = '\0';
    printf("%ld\n", strcspn(s, "\n"));

    printf("%s\n", s);
    printf("%d\n", strcmp(s, "Hello"));
}