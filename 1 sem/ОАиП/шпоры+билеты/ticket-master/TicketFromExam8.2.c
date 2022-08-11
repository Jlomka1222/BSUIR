#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void SwapWords(char* string);
int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("Previous string: %s\n", argv[i]);
        SwapWords(argv[i]);
        printf("New string: %s\n", argv[i]);
    }
    return 0;
}

void SwapWords(char* string)
{
    int start1 = 0, end1 = 0, start2 = 0, end2 = 0;
    int j = 0;
    while (string[j] != '\n' && string[j] != '\0')
    {
        if (string[j] == '\n' || string[j] == '\0')
        {
            break;
        }
        start1 = j;
        while (string[j] != ' ')
        {
            if (string[j] == '\n' || string[j] == '\0')
            {
                break;
            }
            j++;
        }
        end1 = j - 1;
        j++;
        start2 = j;
        while (string[j] != ' ')
        {
            if (string[j] == '\n' || string[j] == '\0')
            {
                break;
            }
            j++;
        }
        end2 = j - 1;
 
        int len1 = end1 - start1;
        int len2 = end2 - start2;
        int pointerEnd2 = end2;
        int pointerStart1 = start1;
        int newEnd2 = start1 + len2;
        int newStart = end2 - len1;

        if (string[start1] > string[start2])
        {
            for (int i = start1; i < pointerEnd2; i++)
            {
                char temp = string[i];
                string[i] = string[pointerEnd2];
                string[pointerEnd2] = temp;
                pointerEnd2--;
            }
            for (int i = start1; i < newEnd2; i++)
            {
                char temp = string[i];
                string[i] = string[newEnd2];
                string[newEnd2] = temp;
                newEnd2--;
            }
            for (int i = end2; i > newStart; i--)
            {
                char temp = string[i];
                string[i] = string[newStart];
                string[newStart] = temp;
                newStart++;
            }
            j = start1 + len2 + 2;
        }

    }
}
