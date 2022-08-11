#include <stdio.h>
#include <stdlib.h>

void povtor(char**, int, int, int*);

int main()
{
	int *povt;
	char** str;
	int n, m;
	povt = (int*)calloc(26, sizeof(int));
	printf("Enter number of strings: ");
	scanf_s("%d", &n);
	printf("Enter number of elements in the string: ");
	scanf_s("%d", &m);
	m++;
	str = (char**)calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		str[i]= (char*)calloc(m, sizeof(char));
	}
	printf("Enter strings:\n");
	rewind(stdin);
	for (int i = 0; i < n; i++)
	{
		fgets(str[i], m, stdin);
		rewind(stdin);
	}
	povtor(str, n, m, povt);
	printf("Number of reiterations:\n");
	for (int i = 0; i < 26; i++)
	{
		printf("%c ", 'a'+i);
	}
	printf("\n");
	for (int i = 0; i < 26; i++)
	{
		printf("%d ", povt[i]);
	}
	for (int i = 0; i < n; i++)
	{
		free(str[i]);
	}
	free(str);
	free(povt);
	return 0;
}

void povtor(char** str, int n, int m, int* povt)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			povt[str[i][j] - 'a']++;
		}
	}
}