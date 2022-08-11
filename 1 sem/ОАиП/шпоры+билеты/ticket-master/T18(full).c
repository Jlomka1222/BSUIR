//-----------------------18.1--------------------------

#include <stdio.h>
#include <malloc.h>

int main()
{
	int summ = 0;
	int n, k;
	int** matrix;
	printf("Enter a size of matrix: \n");
	scanf_s("%d", &n);
	printf("Enter a number of string that you want to sort: \n");
	scanf_s("%d", &k);
	printf("Enter a values: \n");
	

	matrix = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		matrix[i] = (int*)calloc(n, sizeof(int));
		for (int j = 0; j < n; j++)
		{
			printf("[%d][%d]", i, j);
			scanf_s("%d", &matrix[i][j]);
		}
	}

	printf("Entered matrix\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%5d", matrix[i][j]);
		}
		printf("\n");
	} 

	//above the side diagonal

	//printf("\n");
	//int j = 0;
	//for (int i = 0; i < n - 1; i++)
	//{
	//	if (i ==(k - 1))
	//	{

	//		int low = n - 1;
	//		int high = k - 1 + j;
	//		while (high < low)
	//		{
	//			for (int m = high; m < low; m++)
	//			{
	//				if (matrix[i][m] > matrix[i][m + 1])
	//				{
	//					int temp = matrix[i][m];
	//					matrix[i][m] = matrix[i][m + 1];
	//					matrix[i][m + 1] = temp;
	//				}
	//			}
	//			low--;
	//			for (int b = low; b > high;  b--)
	//			{ 
	//				if (matrix[i][b] < matrix[i][b - 1])
	//				{
	//					int temp = matrix[i][b];
	//					matrix[i][b] = matrix[i][b - 1];
	//					matrix[i][b - 1] = temp;
	//				}
	//			}
	//			high++;
	//		}
	//	}
	//	
	//}


	//below the side diagonal
	int i = k - 1;
	int low = n - 1;
	int high = n - i;
	while (high < low)
	{
		{
			for (int m = high; m < low; m++)
			//for(int m = low; m > high; m--)
			{
				if (matrix[i][m] > matrix[i][m + 1])
				{
					int temp = matrix[i][m];
					matrix[i][m] = matrix[i][m + 1];
					matrix[i][m + 1] = temp;
				}
			}
			low--;
			for (int b = low; b > high; b--)
			//for(int b = high; b < low; b++)
			{
				if (matrix[i][b] < matrix[i][b - 1])
				{
					int temp = matrix[i][b];
					matrix[i][b] = matrix[i][b - 1];
					matrix[i][b - 1] = temp;
				}
			}
			high++;
		}
	}

	

	printf("Entered matrix\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%5d", matrix[i][j]);
		}
		printf("\n");
	}



	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; i + j < n - 1; j++)
		{
			if (matrix[i][j] > 0)
			{
				summ += matrix[i][j];
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		free(matrix[i]);
	}
	free(matrix);

	return 0;

}








//--------------------------------------18.2---------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void ReverseLastWord(char* string, int start, int end);
int main()
{
	int i = 0, start = 0, length = 0, count = 0;
	int n;
	char* string;
	printf("Enter a number of elements in string: \n");
	scanf_s("%d", &n);
	string = (char*)calloc(n + 1, sizeof(char));
	rewind(stdin);
	fgets(string, n + 1, stdin);
	puts(string);

	while (string[i] != '\n' && string[i] != '\0')
	{
		i++;
		length++;
	}

	for (int j = length; j > 0; j--)
	{
		while (string[j] != ' ')
		{
			j--;
		}
		if (string[i] = ' ')
		{
			count++;
		}
		start = j + 1;
		if (count == 1)
		{
			break;
		}
	}
	ReverseLastWord(string, start, length);
	puts(string);

	free(string);
	return 0;
}
void ReverseLastWord(char* string, int start, int end)
{
	char temp;
	if (start > end)
	{
		return;
	}

	temp = string[start];
	string[start] = string[end];
	string[end] = temp;

	start++;
	end--;
	ReverseLastWord(string, start, end);
}
