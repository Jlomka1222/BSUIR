#include <stdio.h>
#include <stdlib.h>
#define n 5
#define k 5

int main()
{
	int a[n][k];
	int neg = 0;
	int pos = 0;
	int zer = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			a[i][j] = rand() % 20 - 5;
		}
	}
	printf("Massiv:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (a[i][j] > 0)
				pos += 1;
			else if (a[i][j] == 0)
				zer += 1;
			else if (a[i][j] < 0)
				neg += 1;
		}
	}
	printf("\nKolichestvo polozitelnix chisel: %3d", pos);
	printf("\nKolichestvo otricatelnix chisel: %3d", neg);
	printf("\nKolichestvo chisel ravnix nulu: %3d", zer);
	return 0;
	
}