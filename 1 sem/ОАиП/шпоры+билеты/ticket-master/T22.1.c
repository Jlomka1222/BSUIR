#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

double poisk(double** mt, int k, int n)
{
	double sum = 0, sum_tmp = 0;

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum_tmp += mt[i][j];
		}
		if (sum < sum_tmp)
		{
			sum = sum_tmp;
			sum_tmp = 0;
		}
	}

	return sum;
}

int main()
{
	int n, k;
	double** mt;
	double otvet = 0;

	printf("Input the number of strings: ");
	scanf("%d", &k);
	printf("Input the number of columns: ");
	scanf("%d", &n);

	mt = (double**)malloc(k * sizeof(double*));
	for (int i = 0; i < k; i++)
	{
		mt[i] = (double*)malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			scanf("%lf", &mt[i][j]);
		}
	}

	otvet = poisk(mt, k, n);
	printf("The largest sum is %lf.", otvet);
	return 0;
}
