#include <stdio.h>
#include <malloc.h>
void HorSort(int** matrix, int left, int m);

int main()
{
	int n, m;
	int* matrix;
	printf("Enter a size of matrix \n");
	printf("Enter a number of elements: \n");
	scanf_s("%d", &n);
	/*printf("Enter a number of columns: \n");
	scanf_s("%d", &m);*/
	printf("Enter a values: \n");
	matrix = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		printf("[%d]", i);
		scanf_s("%d", &matrix[i]);
	}

	printf("Entered matrix\n");
	for (int i = 0; i < n; i++)
	{
		printf("%5d", matrix[i]);
		
	}
	printf("\n");
	HorSort(matrix, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		printf("%5d", matrix[i]);
		
	}


	free(matrix);

	return 0;
}

void HorSort(int** matrix, int left, int right)
{
	//int i = 0;
	int lHold = left;
	int rHold = right;
	int pivot = 0;
	
	if (left < right)
	{
		int middle = matrix[(lHold + rHold) / 2];
		do
		{
			while (matrix[lHold] < middle) 
			{
				lHold++; 
			}
			while (matrix[rHold] > middle)
			{
				rHold--;
			}
			if (lHold <= rHold)
			{
				int tmp = matrix[lHold];
				matrix[lHold] = matrix[rHold];
				matrix[rHold] = tmp;
				lHold++;
				rHold--;
			}
		} while (lHold <= rHold);
		HorSort(matrix,left, rHold);
		HorSort(matrix, lHold, right);
	}
	
}
