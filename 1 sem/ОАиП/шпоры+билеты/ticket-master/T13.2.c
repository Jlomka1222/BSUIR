#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//int aToi(char* st)
//{
//	int kl_str, i = 0, znak;
//	while (st[i] == ' ') i++;
//	if (!st[i])
//	{
//		return 0;              // в строке одни пробелы
//	}
//
//	znak = (st[i] == '-') ? -1 : 1;    // запоминаем знак числа
//
//	if (st[i] == '+' || st[i] == '-')  // пропуск знака в строке
//	{
//		i++;
//	}
//	for (kl_str = 0; st[i] >= '0' && st[i] <= '9'; i++)  // выбор символа цифры числа из строки
//	{
//		kl_str = 10 * kl_str + (st[i] - '0');    // формирование числа из цифр строки
//	}
//	return znak * kl_str;                     // возврат числа со знаком
//}

int convertStringToInt(char* string)
{
	int temp = 0;
	int stepen = 0;
	int number = 0;
	int i = 0, start = 0, end = 0;
	int temp_numb = 0;

	while (string[i])
	{
		start = i;
		while (string[i] >= '0' && string[i] <= '9')
		{
			
			i++;
		}
		end = i - 1;

		for (int j = end; j >= start; j--)
		{
			temp = string[j] - '0';
			stepen = end - j;
			number += temp * pow(10, stepen);
		}

		if (temp_numb < number)
		{
			temp_numb = number;
			number = 0;
		}
		
		i++;
	}

	return temp_numb;
}

int main()
{
    char* str;
    int len;
	int otvet=0;

    printf("Input the number of elements in string: ");
	while (scanf_s("%d", &len) == 0)
	{
		printf("You input not a nubmer. Try time more time:"); //проверка на правильность ввода и ввод
		rewind(stdin);
	}

    printf("Input the string with %d elements: ", len);

	len += 1;
    str = (char*)calloc(len, sizeof(char));

	rewind(stdin);
	fgets(str, len, stdin);

	otvet = convertStringToInt(str);

	printf("%d", otvet);

	free(str);
	
	return 0;
}
