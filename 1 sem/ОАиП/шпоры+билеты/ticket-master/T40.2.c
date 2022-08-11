//немного калеченно выводит//
#include <stdio.h>
#include <string.h>
#include <malloc.h>
void ReverseWords(char* string, int length, int start);
int main()
{
	int i = 0, position = 0, start = 0;
	int n;
	char* string;
	printf("Enter a number of elements in string: \n");
	scanf_s("%d", &n);
	string = (char*)calloc(n + 1, sizeof(char));
	rewind(stdin);
	printf("Enter a string: \n");
	fgets(string, n + 1, stdin);
	puts(string);

	while (string[i])
	{
		start = i;
		while (string[i] != ' ' && string[i])
		{
			position++;
			i++;
		}
		ReverseWords(string, position, start);
		//start = i;
		i++;
		//length = 0;
	}

	puts(string);


	free(string);
	return 0;
}

void ReverseWords(char* string, int length, int start)
{
	char temp;
	for (int i = start; i < length; i++, length--)
	{
		temp = string[i];
		string[i] = string[length];
		string[length] = temp;
	}
}
