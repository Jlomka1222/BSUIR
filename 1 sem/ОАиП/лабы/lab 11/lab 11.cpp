#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <conio.h>

void rec(int n)// ������� ��������
{
	if (n < 1)
		return;
	else
	{
		int m;
		scanf_s("%d", &m);
		rec(n - 1);	//����� �������� ������ �������
		printf("%d ", m);
	}
}
int main()
{
	int k;
	printf("vvedite dliny:");
	scanf_s("%d", &k);
	rec(k);	//����� �������
	_getch();
}
