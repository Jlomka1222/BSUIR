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
				for (j = d; j >= c; --j)    // ���� ��������� ��������� ��������� 
				{                           // ������ ������ �� �������
					if (mat[i][j - 1] > mat[i][j])    // ����������� ������� ������������ 
					{                       // (i-1)-��� � i-�� �������� 
						temp = mat[i][j - 1];
						mat[i][j - 1] = mat[i][j];
						mat[i][j] = temp;
						b = j;              // ���������� ������� ����� ������������� �������
					}
				}
				c = b + 1;                  // ����� ���������� �������� ��� ���������� ����� �������
				for (j = c; j <= d; ++j)    // ���������� ����������� �����, �� ��������
				{                           // ����� ������� �� �������
					if (mat[i][j - 1] > mat[i][j])
					{
						temp = mat[i][j - 1];
						mat[i][j - 1] = mat[i][j];
						mat[i][j] = temp;
						b = j;              // ������� ����� ������������� �������
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