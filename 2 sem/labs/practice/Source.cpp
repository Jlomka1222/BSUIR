#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <iostream>
#include <malloc.h>
#pragma warning(disable : 4996)
#define MAX_LEN 100000

int GetInt(void)
{
	int res = 0;
	int chs = 0;
	do {
		res = scanf_s("%d", &chs);
		while (getchar() != '\n');
		if (!res || chs < 0) printf("Неправильный ввод!\n");
	} while (chs < 0 || res != 1);
	return chs;
}

void Pause()
{
	printf_s("\nДля продолжения нажимите любую клавишу: ");
	_getch();
}

int FreqAnalys()
{
	FILE* fout, *fin;;
	char filename_in[MAX_LEN];
	char filename_out[MAX_LEN];
	int c;
	int* count;
	int i;
	printf("\nВведите имя файла, где нужно провести анализ: ");
	scanf("%s", filename_in);
	if ((fin = fopen(filename_in, "r")) == NULL)
	{
		printf("\nНе удалось открыть файл. \n ");
		Pause();
		return -1;
	}
	printf("\nВведите имя файла, куда вывести результаты: ");
	scanf("%s", filename_out);
	if ((fout = fopen(filename_out, "w")) == NULL)
	{
		printf("\nНе удалось открыть файл %s на запись. \n ", filename_out);
		Pause();
		return -1;
	}
	count = (int*)malloc(256 * sizeof(int));
	//Инициализируем массив счетчиков
	for (i = 0; i < 256; i++)
	{
		count[i] = 0;
	}
	while ((c = getc(fin)) != EOF)++count[c]; //увеличиваем счетчик на 1
	/*for (i = 64; i < 255; i++)
	{
		if (count[i] != 0)
		{
			for (int j = 0; j < count[i]; j++)
			{
				printf("=");
			}
			printf("\n");
		}
	}*/
	for (i = 64; i <= 255; i++)
	{
		if (count[i] != 0)
		{
			fprintf_s(fout, " %c - %d\n", i, count[i]);
		}
	}
	fclose(fin);
	fclose(fout);
	Pause();
	system("cls");
	return 0;
}
int Encrypt(int n)
{
	FILE* fp1, *fp2;
	char filename_in[MAX_LEN];
	int ENG = 26;
	int flag;
	char c;
	printf_s("\nВведите имя файла, который нужно зашифровать: ");
	scanf("%s", filename_in);
	if ((fp1 = fopen(filename_in, "r")) == NULL)
	{
		printf("\nНе удалось открыть файл. \n ");
		Pause();
		return -1;
	}
	fp2 = fopen("encryptfile.txt", "w");
	c = getc(fp1);
	while (!feof(fp1))
	{
		flag = 0;
		if (c >= 'A' && c <= 'Z')
		{
			c = c + (n % ENG);
			if (c > 'Z') c = 'A' + (c - 'Z')-1;
			fprintf(fp2, "%c", c);
			flag = 1;
		}
		if (c >= 'a' && c <= 'z')
		{
			c = c + (n % ENG);
			if (c > 'z') c = 'a' + (c - 'z')-1;
			fprintf(fp2, "%c", c);
			flag = 1;
		}
		if (!flag) fprintf(fp2, "%c", c);
		c = getc(fp1);
	}
	
	fclose(fp1);
	fclose(fp2);
	printf("Расшифровка завершена успешна!\n");
	Pause();
	return 0;
}
int Decrypt(int n)
{
	FILE *fp1, *fp2;
	char filename_in[MAX_LEN];
	int ENG = 26;
	int flag;
	char c;
	printf_s("\nВведите имя файла, который нужно расшифровать: ");
	scanf("%s", filename_in);
	if ((fp1 = fopen(filename_in, "r")) == NULL)
	{
		printf("\nНе удалось открыть файл. \n ");
		Pause();
		return -1;
	}
	if (!(fp2 = fopen("decryptfile.txt", "w")))
	{
		printf("\nНе удалось открыть файл. \n ");
		Pause();
		return -1;
	}
	c = getc(fp1);
	while (!feof(fp1))
	{
		flag = 0;
		if (c >= 'A' && c <= 'Z')
		{
			c = c - (n % ENG);
			if (c < 'A') c = 'Z' - ('A' - c) + 1;
			fprintf(fp2, "%c", c);
			flag = 1;
		}
		if (c >= 'a' && c <= 'z')
		{
			c = c - (n % ENG);
			if (c < 'a') c = 'z' - ('a' - c) + 1;
			fprintf(fp2, "%c", c);
			flag = 1;
		}
		if (!flag) fprintf(fp2, "%c", c);
		c = getc(fp1);
	}
	fclose(fp1);
	fclose(fp2);
	printf("Расшифровка завершена успешна!\n");
	Pause();
	return 0;
}
void Help()
{
	system("cls");
	printf("\nHelp ");
	printf("\nДля частотного анализа необходимо подготовить файл ");
	printf("\nформата .txt в кодировке Windows.");
	printf("\nДалее следуйте инструкции");
	printf("\nПорядок работы:");
	printf("\n1.Ввести имя файла, откуда будет взять текст для анализа ");
	printf("\n2.Нажать любую клавишу для того, чтобы ");
	printf("\nзакончить работу с функцией");
	printf("\n3.Открыть заданный вами файл вывода и посмотреть результаты");
	printf("\n4.Для дальнейшего использования программы выбирайте нужные вам функции");
	printf("\nи следуйте инструкциям указанным на экране!");
	printf("\nПриятного пользования!");
	printf("\n© Федорович Илья 150503");
	printf("\n===========================================================");
	Pause();
	system("cls");
}
int main(int argc, char** argv) 
{
	system("chcp 1251");
	setlocale(LC_ALL, "rus");
	int num,key;
	system("cls");
	printf("Добро пожаловать в мое приложение!\n");
	printf("Пожалуйства введите ключ который будете использовать в будующем(от 1 до 26): ");
	key = GetInt();
	while (key < 1 || key > 26)
	{
		printf("Введенный ключ находится вне промежутка 1-26\n");
		printf("Пожалуйста введите ключ еще раз");
		key = GetInt();
	}
	do
	{
		system("cls");
		printf("\nВведите номер функции которой хотите воспользоваться:");
		printf("\n1.Открыть меню HELP");
		printf("\n2.Выполнить частотный анализ текста");
		printf("\n3.Зашифровать текст");
		printf("\n4.Расшифровать текст");
		printf("\n5.Выход из программы\n");
		num = GetInt();
		switch (num)
		{
			case(1):
			{
				rewind(stdin);
				Help();
				break;
			}
			case(2):
			{
				FreqAnalys();
				break;
			}
			case(3):
			{
				rewind(stdin);
				Encrypt(key);
				break;
			}
			case(4):
			{
				rewind(stdin);
				Decrypt(key);
				break;
			}
			case(5):
			{
				_Exit(0);
			}
			default:
			{
				printf("Неправильный выбор!");
				break;
			}
		}
	} while (1);
}