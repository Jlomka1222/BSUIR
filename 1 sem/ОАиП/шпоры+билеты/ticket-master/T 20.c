//----------------------------20.1-------------
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int main () 
{
	srand(time(NULL));
	int n, ** mx;
	while (!(scanf_s("%d", &n)) || n <= 0)
		printf("Wrong number\n"); rewind(stdin);
	while (!(mx = (int**)calloc(n, sizeof(int*))))
		printf("Memory not allocated");
	for (int i = 0; i < n; i++)
		while (!(mx[i] = (int*)calloc(n, sizeof(int))))
			printf("Memory not allocated");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mx[i][j] = rand() % 10;
	printf("Matrix :\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d  ", mx[i][j]);
		printf("\n");
	}
	printf("\n");
	int k = 0, N = n - 1, J = 0;
  
  
	while (N != 0) 
	{
		int i = 1;
		while (i <= N)
		{
			if (mx[N][J] == mx[N - i][J + i])
			{
				mx[N - i][J + i] = 0; 
				k = 1;
			}
			i++;
		}
		if (k == 1)
		{
			mx[N][J] = 0;
			k = 0;
		}
		J++;
		N--;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d  ", mx[i][j]);
		printf("\n");
	}
	return 0;
}

//---------------------------20.2.----------
#include<stdio.h>
#include<stdlib.h>
char * delete_space(char* str, int n)
{
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if ((str[i] == ' ') && (str[i + 1] == ' '))
		{
			for (int j = i; j < n - 1; j++)
			{
				str[j] = str[j + 1];
			}
			n--;
			i--;
		}
		else if (k == 0) 
		{
			for (int j = i; j < n - 1; j++)
			{
				str[j] = str[j + 1];
			}
			n--;
			i--;
			k++;
		}
	}
	if (str[n - 1] == ' ') str[n - 1] = '\0';
	else str[n] = '\0';
	return str;
}
 
int main () 
{
	char* str;
	int n;
	while (!(scanf_s("%d", &n)) || n <= 0) 
	{
		printf("Wrong number");
		rewind(stdin);
	}
	str = (char*)calloc((n + 1), sizeof(char));
	rewind(stdin);
	fgets(str, n + 1, stdin);
	rewind(stdin);
	puts("\n");
	puts(str);
	delete_space(str, n);
	puts("\n");
	puts(str);
	free(str);
	return 0;
}
 
 
