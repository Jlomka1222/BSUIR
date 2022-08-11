#define _CRT_SECURE_NO_WARNINGS 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum optype { power = 3, devide = 2, multiply = 2, minus = 1, plus = 1, null = 0 }; // ���������� ��������

struct stack {
	char val[100]; // ��������������� �������� ��������
	optype type; // ��������� ��������, ��������� ��� ����������� ������������  ������
	stack* next;
} *head;

void push(char[], optype);
void push1(stack*);
stack* pop();
void fromRPN(char*, char*); 

int main() 
{
	system("color f0");
	char infix[100], postfix[100]; // ������� � �������� ������
	gets_s(infix);
	fromRPN(infix, postfix);
	printf("%s\n", postfix);
	system("PAUSE");
	return 0;
}

void push1(stack* t) 
{
	t->next = head;
	head = t;
}

void push(char str[], optype type) 
{
	stack* t;
	t =(stack*)calloc(1,sizeof(stack));
	strcpy(t->val, str);
	t->type = type;
	t->next = head;
	head = t;
}

stack* pop() {
	stack* t;
	if (head == NULL) return NULL;
	t = head;
	head = t->next;
	return t;
}

void fromRPN(char* input, char* output) {
	char c, temp[100];
	int p_temp = 0;
	stack* h1, * h2; // ���������� ��� �������� ������ ���� ��������� �����
	optype type;
	head = NULL;
	while (*input)  // ���� ���� ������� ������
	{
		c = (*input);
		if (c >= '0' && c <= '9' || c == '.') //���� ������� ������ ����� �����
		{ 
			temp[p_temp++] = c; //�� ��������� ��� �� ��������� ������
			temp[p_temp] = '\0';
		}
		else if (c == ' ')
		{
			if (p_temp != 0)
			{
				push(temp, null); // ��������� ����� � ����
				p_temp = 0;
			}
			temp[0] = '\0'; // ���������� ��������� ������
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') //���� ������ ���� ��������
		{ 
			h1 = pop(); // ����������� ������ �������
			h2 = pop(); // ����������� ������ �������
						// ������� ��������� ��������
			if (c == '+') type = plus;
			else if (c == '-') type = minus;
			else if (c == '*') type = multiply;
			else if (c == '/') type = devide;
			else if (c == '^') type = power;
			if (h2->type != NULL && h2->type < type) // ���� ��������� ��� 1-�� �������� ������
			{ 
				temp[0] = '('; temp[1] = '\0'; // ����� ��������� � ������
				h2->val[strlen(h2->val) + 2] = '\0';
				h2->val[strlen(h2->val) + 1] = c; // ����������� ���� ��������
				h2->val[strlen(h2->val)] = ')';
			}
			else 
			{
				h2->val[strlen(h2->val) + 1] = '\0';
				h2->val[strlen(h2->val)] = c;
			}
			strcat(temp, h2->val);
			if (h1->type != null && h1->type < type) // ���� ��������� ��� 2-�� �������� ������
			{  
				strcat(temp, "(");
				h1->val[strlen(h1->val) + 1] = '\0';
				h1->val[strlen(h1->val)] = ')'; // ����� ��������� � ������
			}
			strcat(temp, h1->val);
			strcpy(h2->val, temp); // ��� �� �� �������� ������ ��� ����� �������, �������� ���������� ��������� �� ������ �������
			free(h1); // ������� ������ �������
			h2->type = type; // ������������� ����� ��������� ��������
			push1(h2); // ��������� ����� ������� � ����
		}
		input++;
	}
	strcpy(output, (pop())->val); // �������� ��������� �� ������� ����� � ������ ����������
}
//8 2 5 * + 1 3 2 * + 4 - /
//(8+2*5)/(1+3*2-4)
