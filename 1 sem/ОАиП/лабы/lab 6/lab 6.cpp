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
		printf("������� ����������� �������/�������:");
		i = scanf_s("%d %d", &n, &m);

	} while (i < 2 || n <= 0 || m <= 0);
	if ((ms = (int*)malloc(n * m * sizeof(int))) == NULL)
	{
		printf("������ ����");
		return 0;
	}
	printf("\n������� �������� � ������� MS\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			printf("MS[%d][%d]= ", i, j);
			scanf_s("%d", ms + i * m + j);
		}
	system("CLS");
	system("CLS");
	printf("\n���c�� (�������)\n ");
	for (i = 0; i < n; i++)
	{
		printf("\n");
		for (j = 0; j < m; j++)
			printf("%3d", *(ms + i * m + j));
	}

	for (i = 0; i < n; i++)			 //����� ������������� �������� ������
	{
		ind = 0;						// ind == 1 - ������� ���������� �������� �����
		i1 = i; j1 = 0;                // ��������� ���������� ��� ������ �������� �����
		for (j = 0; j < m; j++)
			if (*(ms + i * m + j) > *(ms + i1 * m + j1))
			{
				i1 = i; j1 = j;            // ���������� ����� ���������� ��� �������� �����
			}
		for (i2 = 0; i2 < n; i2++)
			if (*(ms + i1 * m + j1) >= *(ms + i2 * m + j1) && i1 != i2) break; // ������� ms[i1][j1] - ����� �� �����
		if (i2 >= n)						// �.�. � ��-�� �� ������� �������� ������� ms[i1][j1]
		{                              // ������������� ms[i1][j1] - �������� �����
			printf("\n�������� ����� = %d  \n���������� : MS[%d][%d] ", *(ms + i1 * m + j1), i1, j1);
			ind = 1;                   // ���� �������� ����� � �������
		}

	}

	if (ind)  printf("\n�������� ����� ��� � ������� ");
	free(ms);						    // ������������ ������ �� ������� ���������  ms
	_getch();
}