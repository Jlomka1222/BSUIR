#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	char* str;

	printf("Input the number of symbols: ");
	while (scanf("%d", &n) == 0)
	{
		printf("Try again.");
		rewind(stdin);
	}

	str=(char*)calloc(n+1, sizeof(char));
	printf("Input the string:\n");
	rewind(stdin);
	fgets(str, n + 1, stdin);

	int slovo;
	printf("Input the number of the word: ");
	scanf("%d", &slovo);

	int i = 0;
	int kl=0;

	while (str[i]!='\0' && str[i]!= '\n')
	{
		if (str[i] == ' ')
		{
			kl++;
		}
		if (kl == slovo - 1)
		{
			i++;
			break;
		}
		i++;
	}
	
	int first_start = i;
	int first_end;

	while (str[i] != ' ') 
	{
		i++;
	}

	first_end = i - 1;
	i++;

	int second_start, second_end;
	
	if (str[i] != '\n' && str[i] != '\0')
	{
		second_start = i;
		while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		{
			i++;
		}
		second_end = i - 1;
		int j;

		for (i = first_start, j = second_end; i < j; i++, j--)
		{
			char temp = str[i];
			str[i] = str[j];
			str[j] = temp;
		}

		for (i = first_start, j = first_start + second_end-second_start ; i < j; i++, j--)
		{
			char temp = str[i];
			str[i] = str[j];
			str[j] = temp;
		}
		for (i = first_start + second_end - second_start + 2, j = second_end; i < j; i++, j--)
		{
			char temp = str[i];
			str[i] = str[j];
			str[j] = temp;
		}
	}
	else
	{
		return 0;
	}

	puts(str);
	return 0;
}
