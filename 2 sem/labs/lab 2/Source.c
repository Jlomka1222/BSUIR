#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void showArray(int* ar, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (ar[i] != 0)
			printf("סמסעמÿשטו טח %d סטלגמכמג: %d\n", i + 1, ar[i]);
	}
}

void function(const char* filename)
{
	FILE* f;
	char ch;
	int k = 0;
	int count, n = 0;
	int* ar = (int*)calloc(100, sizeof(int));
	if (!ar)
		return;
	for (int i = 0; i < 100; i++)
		*(ar + i) = 0;
	f = fopen(filename, "r");
	if (!f)
		return;
	while (!feof(f))
	{
		
		count = 0;
		while (/*(ch = fgetc(f)) != ' ' && ch != '\n' && ch != EOF &&*/ (ch = fgetc(f))<='z' && ch>='a' || ch<='Z' && ch>='A')
		{
			count++;
		}
		
		if (count) 
		{
			ar[count - 1]++;
			n++;
		}
	}
	showArray(ar, n);
	free(ar);
}

int main()
{
	system("color F0");
	setlocale(LC_ALL, "RUS");
	function("text.txt");
	return 0;
	system("pause");
}
