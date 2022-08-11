#include <stdio.h>
#include <stdlib.h>

void revers(char* str, int startword, int endword);

int main()
{
	char* str;
	int n;

	scanf_s("%d", &n);
	if(!(str = (char*)calloc(n + 1, sizeof(char)))) return 0;
	rewind(stdin);
	fgets(str, n + 1, stdin);
	printf("\n");
	puts(str);


	int startword, endword, i = 0;
	while (str[i])
	{

		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			i++;
		}
		
		startword = i;
		while (str[i] != ' ' && str[i] != '\0' && str[i] != '\t')
		{
			i++;
		}
		endword = i-1;

		revers(str, startword, endword);
	}

	printf("\n");
	puts(str);

	free(str);
	return 0;
}

void revers(char* str, int startword, int endword)
{
	int temp;
	if (startword > endword)
	{
		return;
	}
	temp = str[startword];
	str[startword] = str[endword];
	str[endword] = temp;
	startword++;
	endword--;
	revers(str, startword, endword);
}
