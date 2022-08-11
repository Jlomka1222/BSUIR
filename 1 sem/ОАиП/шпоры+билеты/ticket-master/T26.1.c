#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void mix(int* arr1, int* arr2, int n1, int n2)
{
	int n3;
	n3 = n1 + n2;
	int* arr3 = (int*)calloc(n3, sizeof(int));
	int i = 0, j = n2-1;
	for (int k = 0; k < n3; k++)
	{
		if (arr1[i] >= arr2[j])
		{
			if (j != 0)
			{
				arr3[k] = arr2[j];
				j--;
			}
			else
			{
				arr3[k] = arr1[i];
				i++;
			}
		}
		else
		{
			if (i != n1)
			{
				arr3[k] = arr1[i];
				i++;
			}
			else
			{
				arr3[k] = arr2[j];
				j--;
			}
		}
	}
	for (int i = 0; i < n3; i++)
	{
		printf("%3d ", arr3[i]);
	}
}

int main()
{
	int n1, n2, temp;
	int* arr1, * arr2;
	scanf_s("%d", &n1);
	scanf_s("%d", &n2);
	arr1 = (int*)calloc(n1, sizeof(int));
	arr2 = (int*)calloc(n2, sizeof(int));
	for (int i = 0; i < n1; i++)
	{
		scanf_s("%d", &temp);
		if (i == 0) arr1[i] = temp;
		else
		{
			if (temp > arr1[i - 1])
			{
				arr1[i] = temp;
			}
			else
			{
				i--;
				printf("Incorrect value, try again");
			}
		}
	}
	system("CLS");
	for (int i = 0; i < n2; i++)
	{
		scanf_s("%d", &temp);
		if (i == 0) arr2[i] = temp;
		else
		{
			if (temp < arr2[i - 1])
			{
				arr2[i] = temp;
			}
			else
			{
				i--;
				printf("Incorrect value, try again");
			}
		}
	}
	system("CLS");
	for (int i = 0; i < n1; i++)
	{
		printf("%3d ", arr1[i]);
	}
	printf("\n");
	for (int i = 0; i < n2; i++)
	{
		printf("%3d ", arr2[i]);
	}
	printf("\n");
	mix (arr1, arr2, n1, n2);
	free(arr1);
	free(arr2);
	return 0;
}