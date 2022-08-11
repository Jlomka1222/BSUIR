#include <stdio.h>
#include <stdlib.h>

void deletefirstsymbol(char* str, int n)
{
	char a = str[0];
	for (int i = 0; i < n; i++)
	{
		while (str[i] == a)
		{
			int k = i;
			for (i; i < n; i++)
			{
				str[i] = str[i + 1];
			}
			i = k - 1;
		}
	}
	puts(str);
}

int main()
{
	int n;
	char* str;
	scanf_s("%d", &n);
	n++;
	str = (char*)calloc(n, sizeof(char));
	rewind(stdin);
	fgets(str, n, stdin);
	deletefirstsymbol(str, n);
	free(str);
	return 0;
}