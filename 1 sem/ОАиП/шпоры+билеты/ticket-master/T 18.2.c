#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
void  reverse(char* str, int start, int last_word) 
{
	static int i;
	char c;
	c = *(str + start + (i++));
	if (c) reverse(str, start, last_word);
	else return;
	*(str + start + last_word - (--i)) = c;
}
int main () 
{
	int len;
	char* str;
	scanf("%d", &len);
	str = (char*)calloc(len + 1, sizeof(char));
	rewind(stdin);
	fgets(str, len + 1, stdin);
	rewind(stdin);
	printf("Total string : \n");
	puts(str);
	int i = len - 1, end, start;
	while (str[i] == ' ')
		i--;
	end = i;
	while (str[i] != ' ' && i >= 0)
		i--;
	start = i + 1;
	int last_word = end + 1 - start;
	reverse(str, start, last_word);
	puts(str);
	return 0;
}
