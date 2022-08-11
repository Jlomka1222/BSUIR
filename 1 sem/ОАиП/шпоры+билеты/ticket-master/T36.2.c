#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int TrueOrFalse(char* string);
int main()
{
	int n, result = 0;
	char* string;
	printf("Enter a size of string: \n");
	scanf_s("%d", &n);
	string = (char*)calloc(n + 1, sizeof(char));
	rewind(stdin);
	printf("Enter string: \n");
	fgets(string, n + 1, stdin);
	puts(string);
	result = TrueOrFalse(string);
	if (result > 0 || result < 0)
	{
		printf("False");
	}
	else
	{
		printf("True");
	}
	return 0;
}

int TrueOrFalse(char* string)
{
	static int i;
	static int a;
	if (string[i] == ' ')
	{
		i++;
		TrueOrFalse(string);
	}
	if (string[i] == '[')
	{
		a++;
		i++;
		TrueOrFalse(string);
	}
	if (string[i] == ']')
	{
		a--;
		i++;
		TrueOrFalse(string);
	}
	if (string[i] == '\0' || string[i] == '\n')
	{
		return a;
	}
	
}
