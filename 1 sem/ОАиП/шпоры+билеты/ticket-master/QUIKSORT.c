#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

void qsortRecursive(int* mas, int size) {
//Указатели в начало и в конец массива
int i = 0;
int j = size - 1;

//Центральный элемент массива
int mid = mas[size / 2];

//Делим массив
do {
//Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
//В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
while (mas[i] < mid) {
i++;
}
//В правой части пропускаем элементы, которые больше центрального
while (mas[j] > mid) {
j--;
}

//Меняем элементы местами
if (i <= j) {
int tmp = mas[i];
mas[i] = mas[j];
mas[j] = tmp;

i++;
j--;
}
} while (i <= j);


//Рекурсивные вызовы, если осталось, что сортировать
if (j > 0) {
// левый кусок"
qsortRecursive(mas, j + 1);
}
if (i < size) {
// правый кусок"
qsortRecursive(&mas[i], size - i);
}
}

int main ()
{
int n = 7, *mas;
mas = (int*)calloc(n, sizeof(int));
for (int i = 0; i < n; i++)
{
scanf("%d", &mas[i]);
}
system("cls");
for (int i = 0; i < n; i++)
{
printf("%4d", mas[i]);
}
puts("\n");
qsortRecursive(mas, n);
for (int i = 0; i < n; i++)
{
printf("%4d", mas[i]);
}
return 0;
}
