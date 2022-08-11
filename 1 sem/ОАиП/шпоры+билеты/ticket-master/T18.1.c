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

	printf("\n");
	int j = 0;
	for (int i = 0; i < n - 1; i++)
	{
		if (i ==(k - 1))
		{

			int low = n - 1;
			int high = k - 1 + j;
			while (high < low)
			{
				for (int m = high; m < low; m++)
				{
					if (matrix[i][m] > matrix[i][m + 1])
					{
						int temp = matrix[i][m];
						matrix[i][m] = matrix[i][m + 1];
						matrix[i][m + 1] = temp;
					}
				}
				low--;
				for (int b = low; b > high;  b--)
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
