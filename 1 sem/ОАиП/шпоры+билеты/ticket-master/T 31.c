//-------------------------31.1-------------

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void insert_sort(int* mas, int n)
{
	for (int i = 0; i < n; i++)
	{
		int x = mas[i];
		int j = i;
		while (j >= 0 && mas[j - 1] > x) 
		{
			mas[j] = mas[j - 1];
			j--;
		}
		mas[j] = x;
	}
}
void shellsort(int* mas, int n) 
{
	int d = (n + 1) / 2;
	while (d != 0) 
	{
		for (int i = 0; i + d < n; i++)
		{ 
			int x = mas[i + d];
			int j = i + d;
			while (j - d >= 0 && mas[j - d] < x) 
			{
				mas[j] = mas[j - d];
				j = j - d;
			}
			mas[j] = x;
		}
		d = d / 2;
	}
}
int main () 
{
	int* mas, n;
	scanf("%d", &n);
	mas = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &mas[i]);
	}
	system("cls");
	printf("Total mas : \n");
	for (int i = 0; i < n; i++)
	{
		printf("%4d", mas[i]);
	}
	puts("\n");
	shellsort(mas, n);
	printf("New mas : \n");
	for (int i = 0; i < n; i++)
	{
		printf("%4d", mas[i]);
	}
	return 0;
}

//------------------------31.2--------------

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void space_delete(char* str, int len)
{
	static int i, k;
	if (str[i] == ' ' && str[i + 1] == ' ')
	{
		for (int j = i; j < len; j++)
		{
			str[j] = str[j + 1];
		}
		len--;
		space_delete(str, len);
	}
	else if (str[i] == ' ' && k == 0)
	{
		k++;
		for (int j = i; j < len; j++)
		{
			str[j] = str[j + 1];
		}
		len--;
		space_delete(str, len);
	}
	else 
	{
		i++;
		if (str[i] != '\0')
			space_delete(str, len);
		else if (str[i - 1] == ' ')
		{
			str[i - 1] = str[i];
		}
	}
 
 
}
int main () 
{
	int len;
	scanf("%d", &len);
	char* str;
	str = (char*)calloc(len + 1, sizeof(char));
	rewind(stdin);
	fgets(str, len + 1, stdin);
	rewind(stdin);
	system("cls");
	printf("Total string : ");
	puts(str);
	printf("New string : ");
	space_delete(str, len);
	puts(str);
	return 0;
}
