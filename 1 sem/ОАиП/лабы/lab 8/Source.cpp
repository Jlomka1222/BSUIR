#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

void delet(char* ms, char* ma, int n)			//удаление одинаковых элементов
{
	int k;
	for (int i = 0; *(ma + i); i++)					// цикл по строке а
	{
		for (int j = 0; *(ms + j); j++)				//цикл по строке s
		{
			if (*(ms + j) == *(ma + i))				//если символ в строке а совпадает с символом в строке s
			{
				for (k = j; *(ms + k) != '\0'; k++)
					*(ms + k) = *(ms + k + 1);				//начина€ со следующего элемента сместить все элементы на 1 влево

			}
		}
	}
}

void show(char* ms) //вывод итоговой строки
{
	if (*ms == '\0')
		printf("\nIz stoki ydalini vse simvoly\n");
	else
		puts(ms);
}

int strlen(char* ms)//вычисление длины строки
{
	int n=0;
	while (*(ms + n) != '\0')
	n++;
	return 0;
}

int prav(int ss, int sa, int k, int u)
{
	if (ss != sa)														//если длина строки s не равна длине строки ј					
	{
		printf("\nStroki dolzni bit' odinakovie po razmeru!!!");
		u++;
	}
	if (ss != k || sa != k)												//неправильна€ размерность строк
	{
		printf("\nStroki dozni soderzat' %4d simvolov", k);
		u++;
	}
	return u;
}

int main()
{
	int k, u;
	char ss, sa;
	char* s, * a;
	printf("Vvedite razmer strok: ");
	scanf_s("%d", &k);
	system("CLS");
 	s = (char*)malloc(k * sizeof(char));
	a = (char*)malloc(k * sizeof(char));
	do
	{
		printf("\nvvedite stroku s(%3d simvolov):\n", k);
		
		fgets(s,k*sizeof(char),stdin);													 // ввод строки s
		ss = strlen(s);												 // определение длины строки s
		printf("\nvvedite stroku a :\n");
		rewind(stdin);
		fgets(a,k*sizeof(char),stdin);													// ввод строки a
		sa = strlen(a);												 // определение длины строки a
		u = 0;
		u = prav(ss, sa, k, u);										 // определение количества ошибок ввода
	} while (u == 0);
	delet(s, a, k);
	system("CLS");
	printf("Preobrazovannaya stroka:");
	show(s);
	_getch();
}
