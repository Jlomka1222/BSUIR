#include <stdio.h>

void DeleteSpaces (char* str) 
{
    int x = 0;
    for (int i = 0; str[i]; i++)
    {
        if ((str[i] != ' ') || (i > 0 && (str[i - 1] != ' ')))
        {
            str[x] = str[i];
            x++;
        }
    }
    str[x] = '\0';
}


int main(int argc, char** argv) 
{
    for (int i = 1; i < argc; i++)
    {
        printf("Previous string: %s\n", argv[i]);
        DeleteSpaces(argv[i]);
        printf("\nFinish string: %s\n", argv[i]);
    }
    return 0;
}
