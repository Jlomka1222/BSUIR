/*T1.2
В массиве строк найти большее слово и вывести его.*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int n, m, num=0, l1, max=0;
	char** str;
	int l = 0;
	scanf_s("%d%d", &n, &m);
	m++;
	str = (char**)calloc(n, sizeof(char*));
	rewind(stdin);
	for (int i = 0; i < n; i++)
	{
		str[i] = (char*)calloc(m, sizeof(char));
		fgets(str[i], m, stdin);
		rewind(stdin);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			
			if (((str[i][j]) != ' ') && ((str[i][j]) !='\0') && ((str[i][j]) != '\n'))
			{
				l++;
			}
			else 
			{
				if (max < l)
				{
					max = l;
				}
				l = 0;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			if (((str[i][j]) != ' ') && ((str[i][j]) != '\0') && ((str[i][j]) != '\n'))
			{
				l++;
			}
			else
			{
				if (max == l)
				{
					l1 = j - l;
					num = i;
				}
				l = 0;
			}
		}
	}
	for (int i = l1; i < (l1 + max); i++)
	{
		printf("%c", str[num][i]);
	}
	return 0;
}
