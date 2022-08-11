#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void perevod(int, int);

int main()
{
	// setlocale все ломает хз почему
	double n;
	int n1, k, s;
	printf("Enter number (real): ");
	scanf_s("%lf", &n);
	printf("Accuracy: ");
	scanf_s("%d", &k);
	n1 = n; // Отсекаем целую часть
	n = n - n1;
	n = n * pow(10, k); // Переводим десятичную дробь в целое число с определенной точностью
	n1 = n;
	printf("Your number to transfer: %d\n", n1);
	printf("Enter the number of system of counting: ");
	scanf_s("%d", &s);
	perevod(n1,s);
	return 0;
}

void perevod(int chisl, int sys)
{
	char *itog;
	itog = (char*)malloc(20);
	int ost, k=0;
	for(int i=19; chisl>=sys; i--)
	{
		ost = chisl % sys;
		chisl /= sys;
		if (ost > 9)
		{
			itog[i] = ost - 10 + 'a';
			k++;
		}
		else
		{
			itog[i] = ost + '0';
			k++;
		}
	}
	if (ost > 9)
	{
		itog[19-k] = chisl - 10 + 'a';
		k++;
	}
	else
	{
		itog[19-k] = chisl + '0';
		k++;
	}
	for (int i = 20-k; i < 20; i++)
	{
		printf("%c", itog[i]);
	}
}