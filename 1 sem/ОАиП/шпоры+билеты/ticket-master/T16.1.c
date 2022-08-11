#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

void str_print_min(int n, int m, int size, ...);
void printfminword(char* str, int start, int end);

int main()
{
    char** str;
    int n = 0, m = 0;
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
    str_print_min(n,m,n, str);

    for (int i = 0; i < n; i++)
    {
        free(str[i]);
    }
    free(str);
    return 0;
}

void str_print_min(int n, int m, int size, ...)
{
    char** str = NULL;
       
    va_list ap;
    va_start(ap, size);
    
    str = va_arg(ap, char**);

    va_end(ap);

    int start, end, len;
    int min = m;
    int startmin = 0, endmin = 0, strmin = 0;
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
            if (min > len)
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
    for (int j = start; j < end + 1; j++)
    {
        printf("%c", str[j]);
    }
}
