#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
void wordsize(char** str, int n, int m);
void printfminword(char* str, int start, int end);
int main()
{
    char** str;
    int n, m;
    scanf_s("%d", &n);
    scanf_s("%d", &m);

    if (!(str = (char**)calloc(n, sizeof(char*)))) return 1;

    for (int i = 0; i < n; i++)
    {
        if (!(str[i] = (char*)calloc(m + 1, sizeof(char)))) return 1;
    }
    rewind(stdin);
    printf("\nstr\n");
    for (int i = 0; i < n; i++)
    {
        fgets(str[i], m + 1, stdin);
        rewind(stdin);
    }

    printf("\nYour str:\n\n");
    for (int i = 0; i < n; i++)
    {
        fputs(str[i], stdout);
        printf("\n");
    }
    wordsize(str, n, m);

    for (int i = 0; i < n; i++)
    {
        free(str[i]);
    }
    free(str);
    return 0;
}



void wordsize(char** str, int n, int m)
{
    int start, end, len;
    int min = 0;
    int startmin=0, endmin=0, strmin=0;
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        while (str[i][j])
        {
            while (str[i][j] == ' ')
            {
                j++;
            }
            start = j;

            while (str[i][j] != ' ' && str[i][j] != '\0')
            {
                j++;
            }
            end = j;
            len = end - start;
            if (min < len)
            {
                min = len;
                startmin = start;
                endmin = end;
                strmin = i;
            }
        }
    }
    printfminword(str[strmin], startmin, endmin);
}

void printfminword(char* str, int start, int end)
{
    for (int j = start; j < end+1; j++)
    {
        printf("%c", str[j]);
    }
}
