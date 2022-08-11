#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>

int main()
{
	setlocale(LC_ALL, "Russian");
	int* ms, n, m, i, i1, i2, j, j1, kk, ind = 0;
	do
	{
		system("CLS");
		printf("Введите размерность матрицы/массива:");
		i = scanf_s("%d %d", &n, &m);

	} while (i < 2 || n <= 0 || m <= 0);
	if ((ms = (int*)malloc(n * m * sizeof(int))) == NULL)
	{
		printf("Памяти нету");
		return 0;
	}
	printf("\nВведите значения в матрицу MS\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			printf("MS[%d][%d]= ", i, j);
			scanf_s("%d", ms + i * m + j);
		}
	system("CLS");
	system("CLS");
	printf("\nМасcив (матрица)\n ");
	for (i = 0; i < n; i++)
	{
		printf("\n");
		for (j = 0; j < m; j++)
			printf("%3d", *(ms + i * m + j));
	}

	for (i = 0; i < n; i++)			 //поиск максимального элемента строки
	{
		ind = 0;						// ind == 1 - признак отсутствия седловой точки
		i1 = i; j1 = 0;                // начальные координаты для выбора седловой точки
		for (j = 0; j < m; j++)
			if (*(ms + i * m + j) > *(ms + i1 * m + j1))
			{
				i1 = i; j1 = j;            // запоминаем новые координаты для седловой точки
			}
		for (i2 = 0; i2 < n; i2++)
			if (*(ms + i1 * m + j1) >= *(ms + i2 * m + j1) && i1 != i2) break; // меньшее ms[i1][j1] - выход из цикла
		if (i2 >= n)						// т.е. в ст-це не найдено значение меньшее ms[i1][j1]
		{                              // следовательно ms[i1][j1] - седловая точка
			printf("\nседловая точка = %d  \nкоординаты : MS[%d][%d] ", *(ms + i1 * m + j1), i1, j1);
			ind = 1;                   // есть седловая точка в матрице
		}

	}

	if (ind)  printf("\nседловой точки нет в матрице ");
	free(ms);						    // освобождение памяти на которую указывает  ms
	_getch();
}