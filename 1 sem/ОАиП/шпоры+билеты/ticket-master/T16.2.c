#include<stdio.h>
#include<stdlib.h>

void wordsize(char* str);
void sizeNextWord(char* str, int endmin, int startmin, int lenmin);

int main()
{
    char* str;
    int n;
    scanf_s("%d", &n);
    if(!(str = (char*)calloc(n + 1, sizeof(char)))) return 1;
    rewind(stdin);
    fgets(str, n + 1, stdin);
    wordsize(str);
    free(str);
    return 0;
}

void wordsize(char* str)
{
    int start= 0, end = 0, len = 0;
    int i = 0;
    int min = 250;
    int startmin = 0, endmin = 0;
    while (str[i]!='\0' && str[i] != '\n')
    {
        while (str[i] == ' ')
        {
            i++;
        }
        start = i;

        while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
        {
            i++;
        }
        end = i - 1;
        len = end - start +1;
        if (min > len)
        {
            min = len;
            startmin = start;
            endmin = end;
        }
    }
    if (str[endmin+1] == '\n' || str[endmin+1] == '\0')
        return;
    else
    sizeNextWord(str, endmin, startmin, min);
}

void sizeNextWord(char* str, int endmin, int startmin, int lenmin)
{
    int start = 0, end = 0, len =0;
    int i = endmin + 2;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
    {
        start = i;
        while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
            i++;
        end = i - 1 ;
        len = start - end +1;
    }
    int j;
    if (len == lenmin)
    {
        printf("Words are the same size, try again");
        return 0;
    }
    else
    {
        for (i = startmin, j = end; i < j; i++, j--)
        {
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }

        for (i = startmin, j = startmin + len - 1; i < j; i++, j--)
        {
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }
        for (i = startmin + len + 1, j = end; i < j; i++, j--)
        {
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
        }

        puts(str);
    }
}
