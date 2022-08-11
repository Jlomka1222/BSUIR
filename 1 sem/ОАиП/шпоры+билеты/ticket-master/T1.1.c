/*1.1
Tранспонировать матрицу относительно побочной диагонали используя while не создавая новую матрицу*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n;
	int** mat;
	/*while (!(scanf_s("%d",&n) != 1))
	{
		rewind(stdin);
	}*/
	scanf_s("%d", &n);
	mat = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		mat[i] = (int*)calloc(n, sizeof(int));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf_s("%d", &mat[i][j]);
		}
	}
	int i = 0, j = 0, temp;
	while (i<n)
	{
		while (j < n -1 - i)
		{
			temp = mat[i][j];
			mat[i][j] = mat[n - 1 - j][n - 1 - i];
			mat[n - 1 - j][n - 1 - i] = temp;
			j++;
		}
		i++;
		j = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%4d", mat[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		free(mat[i]);
	}
	free(mat);
	return 0;
}