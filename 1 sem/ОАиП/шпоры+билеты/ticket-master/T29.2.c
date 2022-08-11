#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void deletefirstword(char*, int);
void rek(int k);

int main()
{
	setlocale(LC_ALL, "rus");
	char* str;
	int n;
	printf("Ââåäèòå êîë-âî ñèìâîëîâ â ñòðîêå: ");
	scanf_s("%d", &n);
	n++;
	str = (char*)calloc(n, sizeof(char));
	rewind(stdin);
	fgets(str, n, stdin);
	deletefirstword(str, n);
	puts(str);
	free(str);
	return 0;
}

void deletefirstword(char* str, int n)
{
	static int i = 0;
	if (str[i] == ' ')
	{
		for (int k = 0; k < n; k++)
		{
			str[k] = str[k + 1];
		}
		return;
	}
	else
	{
		for (int k = 0; k < n; k++)
		{
			str[k] = str[k + 1];
		}
		deletefirstword(str, n);
	}
}
