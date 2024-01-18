#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>

unsigned int notes[] = { 329, 246, 247, 261, 293, 329, 392, 349 };
unsigned int note_delay = 400;

void PlaySound();
void StateWords();
void CharToBin(unsigned char state, char* str);
void TurnSpeaker(int isActive);
void SetCount(int iDivider);
void Menu();

int main() {
	Menu();
	return 0;
}

void Menu() {
	int choice = 0;
	while (1) {
		system("cls");
		printf("1 - Play sound");
		printf("\n2 - Print channels state words");
		printf("\n0 - Exit");

		printf("\n\nEnter choice: ");
		scanf("%d", &choice);
		if (choice >= 0 && choice <= 2) {
			switch (choice) {
			case 0:
				return;

			case 1:
				PlaySound();
				break;

			case 2:
				StateWords();
				printf("\n\nPress any key to continue: ");
				scanf("%d", &choice);
				break;
			}
		}
	}
}

//������� ����������� ����� ��������� �������
void StateWords()
{
	char* bin_state;
	int iChannel;
	unsigned char state;
	bin_state = (char*)calloc(9, sizeof(char));
	if (bin_state == NULL)
	{
		printf("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	for (iChannel = 0; iChannel < 3; iChannel++)
	{
		switch (iChannel)
		{
		case 0:
		{
			outp(0x43, 0xE2); //������� ����������� �����, 
			//��������������� ������� RBC (������ ��������� ������) � ������ ������ 0
			state = inp(0x40); //������ ����� ��������� ������ 0
			CharToBin(state, bin_state);
			printf("Channel 0x40 word: %s\n", bin_state);
			break;
		}
		case 1:
		{
			bin_state[0] = '\0';
			outp(0x43, 0xE4); //������� ����������� �����, 
			//��������������� ������� RBC (������ ��������� ������) � ������ ������ 1
			state = inp(0x41); //������ ����� ��������� ������ 1
			CharToBin(state, bin_state);
			printf("Channel 0x41 word: %s\n", bin_state);
			break;
		}
		case 2:
		{
			bin_state[0] = '\0';
			outp(0x43, 0xE8); //������� ����������� �����, 
			//��������������� ������� RBC (������ ��������� ������) � ������ ������ 2
			state = inp(0x42); //������ ����� ��������� ������ 2
			CharToBin(state, bin_state);
			printf("Channel 0x42 word: %s\n", bin_state);
			break;
		}
		}
	}
	free(bin_state);
	return;
}

//������� �������� � �������� ���
void CharToBin(unsigned char state, char* str)
{
	int i, j;
	char temp;
	for (i = 7; i >= 0; i--)
	{
		temp = state % 2;
		state /= 2;
		str[i] = temp + '0';
	}
	str[8] = '\0';
}

//������� ��������� �������� ��������
void SetCount(int iDivider) {
	long base = 1193180; //������������ �������
	long kd;
	outp(0x43, 0xB6); //10110110 - ����� 2, �������� 4, ����� 3, ������ 0
	kd = base / iDivider;
	outp(0x42, kd % 256); // ������� ���� ��������
	kd /= 256;
	outp(0x42, kd); //������� ���� ��������
	return;
}

//������� ������ � �����������������
void TurnSpeaker(int isActive) {
	if (isActive) {
		outp(0x61, inp(0x61) | 3); //������������� 2 ������� ���� 11
		return;
	}
	else {
		outp(0x61, inp(0x61) & 0xFC); //������������� 2 ������� ���� 00
		return;
	}
}

//������� ��������������� �����
void PlaySound() {
	for (int i = 0; i < 9; i++) {
		SetCount(notes[i]);
		TurnSpeaker(1); //�������� ����������������
		delay(note_delay); //������������� ������������ ��
		TurnSpeaker(0); //��������� ����������������
	}
}