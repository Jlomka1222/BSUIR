//--------------------------39.1---------------------

#include <stdio.h>
#include <stdlib.h>
void SwapStrings(int** matrix, int n, int m);
int main()
{
	int n, m;
	int** matrix;
	printf("Enter a number of strings: \n");
	scanf_s("%d", &n);
	printf("Enter a number of columns: \n");
	scanf_s("%d", &m);

	printf("Enter a matrix: \n");
	matrix = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		matrix[i] = (int*)calloc(m, sizeof(int));
		for (int j = 0; j < m; j++)
		{
			printf("[%d][%d]", i, j);
			scanf_s("%d", &matrix[i][j]);
		}
	}
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%5d", matrix[i][j]);
		}
		printf("\n");
	}

	SwapStrings(matrix, n, m);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%5d", matrix[i][j]);
		}
		printf("\n");
	}


	for (int i = 0; i < n; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}

void SwapStrings(int** matrix, int n, int m)
{
	int min = 0, max = 0, counter = 0, temp = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (matrix[i][j] % 2 != 0)
			{
				counter++;
			}
			if (temp > counter)
			{
				min = i;
			}
			else
			{
				max = i;
			}
			temp = counter;
		}
		counter = 0;
		//printf("\n");
	}

	printf("\n");

	//printf("max is : %d. min is: %d\n", max + 1, min + 1);
	int j = 0;
	while (j < m)
	{
		temp = matrix[min][j];
		matrix[min][j] = matrix[max][j];
		matrix[max][j] = temp;
		j++;
	}

}





//-------------------------39.2------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void DeleteString(char* string, int start, int end);
int main()
{
	int n;
	int start = 0, end = 0, counter = 0, i = 0;
	char* string;
	printf("Enter a size of string: \n");
	scanf_s("%d", &n);
	string = (char*)calloc(n + 1, sizeof(char));
	rewind(stdin);
	printf("Enter a string: \n");
	fgets(string, n + 1, stdin);

	puts(string);

	while (string[i] != '\0' && string[i] != '\n')
	{
		
		while (string[i] != ' ')
		{
			i++;
		}
		counter++;
		i++;

		if (counter == 1)
		{
			start = i;
			while (string[i] != ' ')
			{
				i++;
			}
			end = i - 1;
			break;
		}
	}
	DeleteString(string, start, end);

	printf("\n");

	puts(string);

	free(string);
	return 0;
}
void DeleteString(char* string, int start, int end)
{
	int length = end - start;
	static int i;
	string[start + i] = string[start + i + length + 1];
	if (string[start + i + length + 1] != '\0')
	{
		i++;
		DeleteString(string, start, end);
	}
	else
	{
		return;
	}

}
