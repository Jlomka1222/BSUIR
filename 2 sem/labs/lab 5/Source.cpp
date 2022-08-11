#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

struct tree
{
	int key;
	int level;
	char word[50];
	tree* L, * R;
};

tree* creat(tree* point, int k)
{
	if (!point)
	{
		if (!(point = (tree*)calloc(1, sizeof(tree))))
		{
			puts("При выделении памяти возникла ошибка!");
			return 0;
		}
		puts("Слово в узле дерева:");
		rewind(stdin);
		scanf("%s", &(point->word));
		point->key = k;
	}
	else if (k < point->key) point->L = creat(point->L, k);
	else if (k > point->key) point->R = creat(point->R, k);
	return point;
}

void show(tree* root)
{
	if (root)
	{
		printf("узел содержит : ключ %d, слово %s\n", root->key, root->word);
		if (root->L) show(root->L);
		if (root->R) show(root->R);
	}
}

void search(tree* point, int key)
{
	static int i;
	static int lenght, min = 51, MINl, height, maxH;
	static int root;
	static char word[50], MIN[50];
	if (point->L)
	{
		if (min > strlen(point->L->word))
		{
			min = strlen(point->L->word);
			for (int j = 0; j < min; j++)
				word[j] = point->L->word[j];
		}
		i++;
		search(point->L, key);
		i--;
		if (i == 0)
		{
			root = point->L->key;
			maxH = height;
			MINl = min;
			for (int j = 0; j < MINl; j++)
				MIN[j] = word[j];
			min = 51;
		}
	}
	if (point->R)
	{
		if (min > strlen(point->R->word))
		{
			min = strlen(point->R->word);
			for (int j = 0; j < min; j++)
				word[j] = point->R->word[j];
		}
		i++;
		search(point->R, key);
		i--;
		if (i == 0)
		{
			if (height > maxH)
			{
				root = point->R->key;
				maxH = height;
				MINl = min;
				for (int j = 0; j < MINl; j++)
					MIN[j] = word[j];
			}
			printf("Корень поддерева максимальной длины %d: %d\n", maxH, root);
			printf("Слово с минимальной длиной %d в этом поддереве= %s", MINl, MIN);
		}
	}
	if (height < i)
		height = i;
	_getch();
}

int GetInt(void)
{
	rewind(stdin);
	int res = 0;
	int chs = 0;
	do {
		res = scanf("%d", &chs);
		while (getchar() != '\n');
		if (!res || chs < 0) printf("Неправильный ввод!\n");
	} while (chs < 0 || res != 1);
	return chs;
}
int main()
{
	system("chcp 1251");
	system("cls");
	int k,num;
	tree* point = nullptr;
	tree* root = point;
	puts("Добро пожаловать!");
	while (1)
	{
		puts("1)Создать дерево");
		puts("2)Вывести дерево");
		puts("3)Провести поиск по дереву");
		puts("4)Выход из программы");
		puts("Выберите операцию");
		num = GetInt();
		switch (num)
		{
			case(1):
			{
				while (1)
				{
					puts("Введите ключ узла дерева");
					puts("Если хотите выйти введите в ключе букву!");
					if (!scanf("%d", &k))
						break;
					point = creat(point, k);
				}
				break;
			}
			case(2):
			{
				show(point);
				break;
			}
			case(3):
			{
				search(point, point->key);
				break;
			}
			case(4):
			{
				_Exit(0);
			}
		}
	}
}

