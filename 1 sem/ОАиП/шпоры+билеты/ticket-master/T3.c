//---------------------------------3.1-----------------------

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int k = 0, b = 0, j = 0;
    int pos1 = 0, pos2 = 0;
    int n;
    float temp = 0.0;
    double* result;
    double* firstArray;
    double* secondArray;
    printf("Enter a number of elements in the first array: \n");
    scanf_s("%d", &n);
    firstArray = (double*)calloc(n, sizeof(double));
    printf("Enter elements: \n");
    for (int i = 0; i < n; i++)
    {
        printf("[%d] ", i + 1);
        scanf_s("%lf", &firstArray[i]);
        while (temp < firstArray[i] && (i != 0))
        {
            printf("Enter again: \n");
            printf("[%d] ", i + 1);
            scanf_s("%lf", &firstArray[i]);
        }
        temp = firstArray[i];
    }

    temp = 0.0;

    printf("Enter a number of elements in the second array: \n");
    secondArray = (double*)calloc(n, sizeof(double));
    printf("Enter elements: \n");
    for (int i = 0; i < n; i++)
    {
        printf("[%d] ", i + 1);
        scanf_s("%lf", &secondArray[i]);
        while (temp < secondArray[i] && (i != 0))
        {
            printf("Enter again: \n");
            printf("[%d] ", i + 1);
            scanf_s("%lf", &secondArray[i]);
        }
        temp = secondArray[i];
    }

    for (int i = 0; i < n; i++)
    {
        printf("%5.2lf  ", firstArray[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%5.2lf  ", secondArray[i]);
    }
    printf("\n");
    result = (double*)calloc(2 * n, sizeof(double));
    while (k < 2 * n)
    {
        while (b < n)
        {
            while (j < n)
            {
                if (firstArray[j] > secondArray[b])
                {
                    result[k] = firstArray[j];
                    k++;
                    j++;
                }
                else
                {
                    result[k] = secondArray[b];
                    k++;
                    b++;
                }
            }
            result[k] = secondArray[b];
            k++;
            b++;
        }
    }
    for (int i = 0; i < 2 * n; i++)
    {
        printf("%10.2lf", result[i]);
    }
    free(result);
    free(firstArray);
    free(secondArray);
    return 0;



//------------------------3.2-----------------------------


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void ReverceWord(char* string, int start, int end);
int main()
{
	int n;
	int end = 0, start = 0, counter = 0, i = 0;
	char* string;
	printf("Enter a number of elements: \n");
	scanf_s("%d", &n);
	if (!(string = (char*)calloc(n + 1, sizeof(char))))
	{
		return -1;
	}

	rewind(stdin);
	printf("Enter a string: \n");
	fgets(string, n + 1, stdin);

	puts(string);

	while (string[i] != '\n' && string[i] != '\0')
	{
		start = i;
		while (string[i] != ' ' && string[i] != '\n')
		{
			i++;
		}
		end = i - 1;
		counter++;
		if (counter % 2 != 0)
		{
			ReverceWord(string, start, end);
		}
		i++;
	}

	puts(string);

	free(string);
	return 0;
}
void ReverceWord(char* string, int start, int end)
{
	for (int i = start; i < end; i++)
	{
		char temp = string[i];
		string[i] = string[end];
		string[end] = temp;
		end--;
	}
}
