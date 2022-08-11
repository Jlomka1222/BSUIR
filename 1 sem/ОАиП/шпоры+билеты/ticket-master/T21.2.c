#include <stdio.h>
#include <stdlib.h>

int minword(char* str, int n)
{
	int min = n, a = 0;
	for (int i = 0; i < n; i++)
	{
		if ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '\n'))
		{
			a++;
		}
		else
		{
			if ((a <= min) && (a!=0))
			{
				min = a;
			}
			a = 0;
		}
	}
	return min;
}

void changemin(char* str, int n, int min)
{
	int a=0, k1, k2, k3;
	char temp;
	for (int i = 0; i < n; i++)
	{
		if ((str[i] != ' ') && (str[i] != '\0') && (str[i] != '\n'))
		{
			a++;
		}
		else
		{
			if (a == min)
			{
				k3 = i-1;
				for (int i = k3; i>=0 ; i--)
				{
					if (str[i] == ' ')
					{
						k2 = i+1;
						i = 0;
					}
					else
						if (i == 0) return;
					
				}
				for (int i = k2 - 2; i >= 0; i--)
				{
					if (str[i] == ' ')
					{
						k1 = i+1;
						i = 0;
					}
					else
						if (i == 0) k1=0;
				}
			}
			a = 0;
		}
	}
	int p = 0;
	for (int i = k1; i < k3; i++)
	{
		if (i <= ((k1 + k3) / 2))
		{
			temp = str[i];
			str[i] = str[k3-p];
			str[k3-p] = temp;
			p++;
		}
		else break;
	}
	p = 0;
	k2 = k1 + min-1;
	for (int i = k1; i < k2; i++)
	{
		if (i <= ((k2+k1) / 2))
		{
			temp = str[i];
			str[i] = str[k2 - p];
			str[k2 - p] = temp;
			p++;
		}
		else break;
	}
	p = 0;
	k2 = k2 + 2;
	for (int i = k2; i < k3; i++)
	{
		if (i <= ((k2+k3) / 2))
		{
			temp = str[i];
			str[i] = str[k3 - p];
			str[k3 - p] = temp;
			p++;
		}
		else break;
	}
	puts(str);
}

int main()
{
	int n, min;
	char* str;
	scanf_s("%d", &n);
	n++;
	str = (char*)calloc(n, sizeof(char));
	rewind(stdin);
	fgets(str, n, stdin);
	min = minword(str, n);
	changemin(str, n, min);
	free(str);
	return 0;
}