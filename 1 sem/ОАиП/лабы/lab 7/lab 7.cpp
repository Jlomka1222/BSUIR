#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

int main()
{
	int** ms;
	int n;
	printf("vvedite razmernost massiva:");			//�������� ����������� �������
	scanf_s("%3d", &n);
	system("CLS");
	ms = (int**)malloc(n * sizeof(int*));			//��������� ������ ��� n ����������
	for (int i = 0; i < n; i++)	
	{
		ms[i] = (int*)malloc(n * sizeof(int));		//��������� ������ ��� ��� ��������� ������ �������
	}
	printf("Massiv razmernosti n*n: \n");			// ����� ������� �� �����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			ms[i][j] = rand() % 20 ;
			printf("%3d ", ms[i][j]);
		}
		printf("\n");
	}
	int	s1=0, s2=0, s3=0;
	for (int i = 0; i < n; i++)					//������ ����� ��������� ������� � ����������� �� �� ��������� � �������
	{
			for (int j = 0; j < n; j++)
			{
				if (i < j) s3 = s3+ms[i][j];		//���� ���������
				if (i == j)s2 = s2+ms[i][j];		//�� ���������
				if (i > j)s1 = s1+ms[i][j];		//���� ���������
			}
	}
		printf("\nsumma elementov raspolozennix nizhe glavnoi diagonali: %4d", s3);
		printf("\nsumma elementov raspolozennix na diagonali: %4d", s2);
		printf("\nsumma elementov raspolozennix vishe glavnoi diagonali: %4d", s1);
	for (int i = 0; i < n; i++)					//�������� ������ ����� ������ ���������
	{
		free(ms[i]);
	}
	free(ms);
	_getch();
}