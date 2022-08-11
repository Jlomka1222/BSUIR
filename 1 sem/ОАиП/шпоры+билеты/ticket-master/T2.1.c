#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
int SumOfIntegers(char* string, int n);
int main()
{
	int sum = 0;
	int n;
	char* string;
	printf("Enter a number of elements in string: \n");
	scanf_s("%d", &n);
	string = (char*)calloc(n + 1, sizeof(char));
	rewind(stdin);
	printf("Enter a string: \n");
	fgets(string, n + 1, stdin);
	puts(string);
	sum = SumOfIntegers(string, n);

	printf("%d", sum);
	free(string);
	return 0;
}
int SumOfIntegers(char* string, int n) 
{
	int length = 0, start = 0, stepen = 0, number = 0, end = 0, sum = 0;
	for (int i = 0; i < n; i++)
	{
		start = i;
		while (string[i] != ' ' && string[i] != '\n')
		{
			i++;
		}
		end = i;
		for (int j = end - 1; j >= start; j--)
		{
			number = string[j] - '0';
			number = number * pow(10, stepen);
			sum += number;
			stepen++;
		}
		stepen = 0;
		
		if (string[i] == '\0' || string[i] == '\n')
		{
			break;
		}
	}
	return sum;
}
