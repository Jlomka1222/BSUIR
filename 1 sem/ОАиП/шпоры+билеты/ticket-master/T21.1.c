#include <stdio.h>
#include <stdlib.h>

void sort(long int**, int);

int main()
{
	int n;
	long int** mat;
	scanf_s("%d", &n);
	mat = (long int**)calloc(n, sizeof(long int*));
	for (int i = 0; i < n; i++)
	{
		mat[i] = (long int*)calloc(n, sizeof(long int));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%ld", &mat[i][j]);
		}
	}
	sort(mat, n);
	for (int i = 0; i < n; i++)
	{
		free(mat[i]);
	}
	free(mat);
	return 0;
}

void sort(long int** mat, int n)
{
	int j; 
	long int temp;
	for (int i = 0; i < n; i++)
	{
		if ((mat[i][0])%2==0)
		{
			int c = 1, b = n - 1, d = n - 1; // b-ostanovka d-start sprava nalevo
			do
			{
				for (j = d; j >= c; --j)    // цикл попарного сравнения элементов 
				{                           // справа налево по массиву
					if (mat[i][j - 1] > mat[i][j])    // выполняется условие перестановки 
					{                       // (i-1)-ого и i-го элемента 
						temp = mat[i][j - 1];
						mat[i][j - 1] = mat[i][j];
						mat[i][j] = temp;
						b = j;              // запоминаем крайний слева упорядоченный элемент
					}
				}
				c = b + 1;                  // номер стартового элемента для сортировки слева направо
				for (j = c; j <= d; ++j)    // аналогично предыдущему циклу, но движение
				{                           // слева направо по массиву
					if (mat[i][j - 1] > mat[i][j])
					{
						temp = mat[i][j - 1];
						mat[i][j - 1] = mat[i][j];
						mat[i][j] = temp;
						b = j;              // крайний слева упорядоченный элемент
					}
				}
				d = b - 1;
			} while (c <= d);
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%3ld", mat[i][j]);
		}
		printf("\n");
	}
}