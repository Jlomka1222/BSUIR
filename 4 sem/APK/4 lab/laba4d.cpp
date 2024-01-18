#include <io.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char new_time[6]; // данные часов
unsigned int delay_count = 0;
unsigned int time_counters[] = { 0x00, 0x02, 0x04, 0x07, 0x08, 0x09 };
unsigned int time_registers[] = { 0x01, 0x03, 0x05};
int alarm_on = 0;

void interrupt time_interrupt(...);  
void interrupt alarm_interrupt(...); 
void interrupt(*old_time_interrupt)(...);
void interrupt(*old_alarm_interrupt) (...);

int dtob(int val);
int btod(int val);
void show_time();
void set_time();
void set_alarm();
void set_delay(unsigned int delay);
void reset_alarm();
void enter_time();
int enter_value(int high_measure, int low_measure);

int dtob(int val)
{
	return (val / 10 * 16) + (val % 10);
}

int btod(int val) 
{
	return (val / 16 * 10) + (val % 16);
}

void show_time()
{

    int i = 0;
    for (i = 0; i < 6; i++) {
        outp(0x70, time_counters[i]); // выбор адреса в памяти CMOS
        new_time[i] = btod(inp(0x71)); // считывание значения по адресу в массив
    }


	printf("%02u:%02u:%02u\n%02u.%02u.20%02u\n", 
			new_time[2], new_time[1], new_time[0], new_time[3], new_time[4], new_time[5]);
}

int enter_value(int high_measure, int low_measure)
{
	int value = 0;
	do
	{
		rewind(stdin);
		scanf("%d", &value);
	} while(value > high_measure || value < low_measure);
	
	return dtob(value);
}

void enter_time()
{
	printf("Enter year:\n");
	new_time[5] = enter_value(100, 21);

	printf("Enter month:\n");
	new_time[4] = enter_value(12, 1);
    
	printf("Enter day:\n");
	new_time[3] = enter_value(31, 1);

    printf("Enter hours:\n");
    new_time[2] = enter_value(23, 0);

    printf("Enter minuts:\n");
    new_time[1] = enter_value(59, 0);
    
    printf("Enter seconds:\n");
    new_time[0] = enter_value(59, 0);
}

void set_time()
{
	enter_time();
	disable();
	
    // проверка на доступность значений для чтения/записи
    unsigned int check;
    do {
        outp(0x70, 0xA); // выбор регистра А
        check = inp(0x71) & 0x80; // 0x80 - 1000 0000
        // 7-й бит в 1 для обновления времени
    } while (check);

    // отключение обновления часов реального времени
    outp(0x70, 0xB); // выбор регистра B
    outp(0x71, inp(0x71) | 0x80); // 0x80 - 1000 0000
    // 7-й бит в 1 для запрета обновления часов

    for (int i = 0; i < 6; i++) {
        outp(0x70, time_counters[i]); // выбор нужного значения данных
        outp(0x71, new_time[i]); // подача в регистр нужного значения
    }

    // включение обновления часов реального времени
    outp(0x70, 0xB); // выбор регистра В
    outp(0x71, inp(0x71) & 0x7F); // 0x7F - 0111 1111
    // 7-й бит в 0 для разрешения обновления часов

    enable(); // разрешение на прерывание
    system("cls");
}


void set_delay(unsigned int delay)
{
	int freq;
	printf("input frequence:\n");
	do
	{
		scanf("%d", &freq);
	}while(freq > 15 || freq < 3);
	
    disable(); // запрет на прерывание

    // установка нового обработчика прерываний
    old_time_interrupt = getvect(0x70);
    setvect(0x70, time_interrupt);
	    // размаскировка линии сигнала запроса от ЧРВ
    // 0xA1 - новое значение счетчика для системного таймера
    outp(0xA1, inp(0xA1) & 0xFE); // 0xFE = 1111 1110
    // 0-й бит в 0 для разрешения прерывания от ЧРВ 

    enable();

	int state;

	disable();
	unsigned int check;
	do
	{
		outp(0x70, 0xA); // выбор регистра A
        check = inp(0x71) & 0x80;
	}while(check);
	outp(0x70, 0xA);
	
	outp(0x71, (inp(0x71) & 0xF0) | freq);
	 // разрешение на прерывание
	enable();
	
    outp(0x70, 0xB); // выбор регистра В
    outp(0x71, inp(0x71) | 0x40); // 0x40 = 0100 0000
    // 6-й бит регистра B установлен в 1 для периодического прерывания

    delay_count = 0;
    while (delay_count <= delay);
	
	disable();
    setvect(0x70, old_time_interrupt);
	enable();
	delay_count = 0;	
	return;
}

void set_alarm()
{
    enter_time(); // ввод нового времени
    disable(); // запрет на прерывание

    // проверка на доступность значений для чтения/записи
    unsigned int check;
    do {
        outp(0x70, 0xA); // выбор регистра A
        check = inp(0x71) & 0x80; // 0x80 - 1000 0000
        // 7-й бит в 1 для обновления времени
    } while (check);

	for(int i = 0; i < 3; i++)
	{
		outp(0x70, time_registers[i]);
		outp(0x71, new_time[i]);
	}	

    outp(0x70, 0xB); // выбор регистра B
    outp(0x71, (inp(0x71) | 0x20)); // 0x20 - 0010 0000
    // 5-й бит регистра B установлен в 1 для разрешения прерывания будильника

    // переопределение прерывания будильника
    old_alarm_interrupt = getvect(0x70); 
    setvect(0x70, alarm_interrupt);
    outp(0xA1, (inp(0xA0) & 0xFE)); // 0xFE - 1111 1110
    // 0-й бит в 0 для разрешения прерывания от ЧРВ

    enable(); // разрешение на прерывание
    alarm_on = 1;
}

void reset_alarm()
{
    // проверка на наличие установленного будильника
    if (old_alarm_interrupt == NULL)
        return;

    disable(); // запрет на прерывание

    // возврат старого прерывания
    setvect(0x4A, old_alarm_interrupt); 
    outp(0xA1, (inp(0xA0) | 0x01)); // 0x01 - 0000 0001 (пересчет частоты прерывания)

    // проверка на доступность значений для чтения/записи
    unsigned int check;
    do {
        outp(0x70, 0xA); // выбор регистра A
        check = inp(0x71) & 0x80;  // 0x80 - 1000 0000
        // 7-й бит в 1 для обновления времени
    } while (check);

    // запись нулевых значений в регистр будильника
for (int i = 0; i < 3; i++)
	{
		outp(0x70, time_registers[i]);
		outp(0x71, 0x00);
	}		
    outp(0x70, 0xB); // выбор регистра B
    outp(0x71, (inp(0x71) & 0xDF)); // 0xDF - 1101 1111
    // 5-й бит в 0 для запрета прерывания будильника

    enable(); // разрешение на прерывание
}

int main() 
{	
	while (1)
	{
		system("cls");
		show_time();
		printf("\n1 - Set time");
		printf("\n2 - Set delay");
		printf("\n3 - Set alarm");
		printf("\n0 - Exit");
		printf("delay_count = %d", delay_count);
		if(alarm_on == 1) printf("\n\nALARM ON");
		if(alarm_on == 2) {
			printf("\n\nALARM!");
			delay(1000);
			alarm_on = 0;
		}
		
		printf("\n\nEnter choice: ");
		delay(1000);
		if (kbhit()) {
			switch(getch())
			{
			case '0':
				return 0;
					
			default:
			break;
				
			case '1':
				system("cls");
				set_time();
			break;
				
			case '2':
				system("cls");
				int delay = 0;
				printf("Input delay (ms): ");
				scanf("%d", &delay);
				set_delay(delay);
			break;
				
			case '3':
				system("cls");
				set_alarm();
			break;
			}
		}
	}
}



void interrupt time_interrupt(...) // новый обработчик прерываний часов
{
    outp(0x70, 0x0C);
	if (inp(0x71) & 0x40) // 0100 0000
	{
		delay_count++;
		printf("delay_count: %d\n", delay_count);
	}
    // посыл сигнала контроллерам прерываний об окончании прерывания
    (*old_time_interrupt)();
}

void interrupt alarm_interrupt(...) // новый обработчик прерываний будильника
{
	system("cls");
	alarm_on = 2;
    old_alarm_interrupt();
    reset_alarm();
}

//00h: RTC — текущая секунда (00 – 59h или 00 – 3Bh) — формат выбирается регистром 0Bh, по умолчанию — BCD

//01h: RTC — секунды будильника (00 – 59h или 00 – 3Bh или FFh (любая секунда))

//02h: RTC — текущая минута (00 – 59h или 00 – 3Bh)

//03h: RTC — минуты будильника (00 – 59h или 00 – 3Bh или FFh)

//04h: RTC — текущий час:
//		0 – 23h/00 – 17h (24-часовой режим)
//		1 – 12h/01 – 1Ch (12-часовой режим до полудня)
//		81h – 92h/81 – 8Ch (12-часовой режим после полудня)

//05h: RTC — часы будильника (то же или FFh, если любой час)

//06h: RTC — текущий день недели (1 – 7, 1 — воскресенье)

//07h: RTC — текущий день месяца (01 – 31h/01h – 1Fh)

//08h: RTC — текущий месяц (01 – 12h/01 – 0Ch)

//09h: RTC — текущий год (00 – 99h/00 – 63h)

//0Ah: RTC — регистр состояния А
//		бит 7: 1 — часы заняты (происходит обновление)
//		биты 4 – 6: делитель фазы (010 — 32 768 KHz — по умолчанию)
//		биты 3 – 0: выбор частоты периодического прерывания:
//			0000 — выключено
//			0011 — 122 микросекунды (минимум)
//			1111 — 500 миллисекунд
//			0110 — 976,562 микросекунды (1024 Hz)

//0Bh: RTC — регистр состояния В
//		бит 7: запрещено обновление часов (устанавливают перед записью новых значений в регистры даты и часов)
//		бит 6: вызов периодического прерывания (IRQ8)
//		бит 5: вызов прерывания при срабатывании будильника
//		бит 4: вызов прерывания по окончании обновления времени
//		бит 3: включена генерация прямоугольных импульсов
//		бит 2: 1/0 — формат даты и времени двоичный/BCD
//		бит 1: 1/0 — 24-часовой/12-часовой режим
//		бит 0: автоматический переход на летнее время в апреле и октябре

//0Ch только для чтения: RTC — регистр состояния С
//		бит 7: произошло прерывание
//		бит 6: разрешено периодическое прерывание
//		бит 5: разрешено прерывание от будильника
//		бит 4: разрешено прерывание по окончании обновления часов

//0Dh только для чтения: регистр состояния D
//		бит 7: питание RTC/CMOS есть

