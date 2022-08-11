//На экзамине писать только реализацию функции

#include <stdio.h>
#include <stdlib.h>

void sort_gl_daig(int** mt, int  kl_col_str);

int main() 
{

    int** mt;
	int kl_col_str;

	printf("Enter the number of columns and strings: ");
	scanf_s("%d", &kl_col_str);

	mt = (int**)malloc(kl_col_str * sizeof(int*));
	for (int i = 0; i < kl_col_str; i++)
	{
		mt[i] = (int*)malloc(kl_col_str * sizeof(int));
	}

	printf("Input the matrix: \n");
	for (int i = 0; i < kl_col_str; i++)
	{
		for (int j = 0; j < kl_col_str; j++)
		{
			scanf_s("%d", &mt[i][j]);
		}
	}

	sort_gl_daig(mt, kl_col_str);

	printf("New matrix: \n");
	for (int i = 0; i < kl_col_str; i++)
	{
		for (int j = 0; j < kl_col_str; j++)
		{
			printf("%3d", mt[i][j]);
		}

		printf("\n");
	}

	for (int i = 0; i < kl_col_str; i++)
	{
		free(mt[i]);
	}
	free(mt);

	return 0;
}

void sort_gl_daig(int** mt,int  kl_col_str)
{
	int k;

	for (int i = 1; i < kl_col_str; i++)
	{
		k = i;

		while (k > 0 && mt[k - 1][k - 1] < mt[k][k])
		{
			int tmp = mt[k - 1][k - 1];
			mt[k - 1][k - 1] = mt[k][k];
			mt[k][k] = tmp;

			k -= 1;
		}

	}
}
