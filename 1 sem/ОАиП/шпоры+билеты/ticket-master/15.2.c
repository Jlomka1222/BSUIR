#include <stdio.h>
#include<stdlib.h>
#include<locale.h>

int check(char* ms)
{
	int k = 0;
	while (ms[k] != ' ' && ms[k] != '\n')
	{
		if (ms[k] >= 'a' && ms[k] < 'a' + 15)
		{
			k++;
		}
		else
		{
			return(0);
		}
	}
	return(1);
}

void wordprintf(char* ms)
{
	int k = 0;
	while (ms[k] != ' ' && ms[k] != '\n')
	{
		printf("%c", ms[k]);
		k++;
	}
}

int main()
{

	setlocale(LC_ALL, "Russian");

	char*** str;
	int amount_str, amount_cmns, str_size;

	printf("введите кол-во строк: ");
	scanf_s("%d", &amount_str);

	printf("\nвведите кол-во столбцов: ");
	scanf_s("%d", &amount_cmns);

	printf("\nвведите размер одной строки: ");
	scanf_s("%d", &str_size);

	str = (char***)calloc(amount_str, sizeof(char**));
	for (int i = 0; i < amount_str; i++)
	{
		str[i] = (char**)calloc(amount_cmns, sizeof(char*));
		for (int j = 0; j < amount_cmns; j++)
		{
			str[i][j] = (char*)calloc(str_size, sizeof(char));
			rewind(stdin);
			printf("\nвведите строку: ");
			fgets(str[i][j], str_size, stdin);
		}
	}

	for (int i = 0; i < amount_str; i++)
	{
		for (int j = 0; j < amount_cmns; j++)
		{
			puts(str[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < amount_str; i++)
	{
		for (int j = 0; j < amount_cmns; j++)
		{
			if (check(str[i][j]) == 1)
			{
				printf("\nслово: ");
				wordprintf(str[i][j]);
			}
			printf("\n");
		}
	}

	for (int i = 0; i < amount_str; i++)
	{
		for (int j = 0; j < amount_cmns; j++)
		{
			free(str[i][j]);
		}
	}

	for (int i = 0; i < amount_str; i++)
	{
		free(str[i]);
	}
	free(str);
	return(0);
}
