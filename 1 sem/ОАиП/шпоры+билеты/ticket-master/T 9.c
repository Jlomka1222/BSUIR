//Нужна только функция


#include <stdio.h>
#include <malloc.h>
void SortByInsert(int** matrix, int index, int m);
int main()
{
	int n, m, index;
	int** matrix;

	printf("Enter size of matrix\n");
	printf("Enter number of strings: \n");
	scanf_s("%d", &n);
	printf("Enter number of columns: \n");
	scanf_s("%d", &m);

	printf("Enter a matrix\n");
	matrix = (int**)calloc(n, sizeof(int*));
	{
		for (int i = 0; i < n; i++)
		{
			matrix[i] = (int*)calloc(m, sizeof(int));
				for (int j = 0; j < m; j++)
				{
					printf("[%d][%d] ", i, j);
					scanf_s("%d", &matrix[i][j]);
					//printf("\n");
				}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%5d", matrix[i][j]);
		}
		printf("\n");
	}

	printf("Enter a string that you want to sort: \n");
	scanf_s("%d", &index);
	SortByInsert(matrix, index - 1, m);

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

void SortByInsert(int** matrix, int index, int m)
{
	int temp = 0, location = 0;
	for (int j = 1; j < m; j++)
	{
		temp = matrix[index][j];
		location = j - 1;
		while (location >= 0 && matrix[index][location] > temp)
		{
			matrix[index][location + 1] = matrix[index][location];
			location--;
		}
		matrix[index][location + 1] = temp;
	}
}




#include <stdio.h>
#include <string.h>
#include <malloc.h>
void SwapWords(char* string);
int main()
{
	int n;
	char* string;
	printf("Enter a number of elements in string: \n");
	scanf_s("%d", &n);
	string = (char*)calloc(n + 1, sizeof(char));
	rewind(stdin);
	printf("Enter a string: \n");
	fgets(string, n + 1, stdin);
	puts(string);

	SwapWords(string);

	puts(string);


	free(string);
	return 0;
}

void SwapWords(char* string)
{
	int length = 0;
	int position = 0;
	int firstWord = 0;
	int secondWord = 0;
	int counter = 0;
	int i = 0;
	while (counter != 1)
	{
		i++;
		firstWord++;
		if (string[i] == ' ')
		{
			counter++;
			i++;
		}
		
		if (counter == 1)
		{
			while (string[i] != ' ')
			{
				i++;
				secondWord++;
			}
			position = i;
		}
	}

	//reverse
	length = position;
	for (int i = 0; i < position; i++)
	{
		char temp;
		temp = string[i];
		string[i] = string[position - 1];
		string[position - 1] = temp;
		position--;
	}

	puts(string);
	int tempPosition = secondWord;

	for (int i = 0; i < secondWord; i++)
	{
		char temp;
		temp = string[i];
		string[i] = string[secondWord - 1];
		string[secondWord - 1] = temp;
		secondWord--;
	}
	puts(string);
	
	
	for (int i = tempPosition + 1; i < tempPosition + firstWord + 2; i++)
	{
		char temp;
		temp = string[i];
		string[i] = string[tempPosition + firstWord];
		string[tempPosition + firstWord] = temp;
		tempPosition + firstWord--;
	}
}
