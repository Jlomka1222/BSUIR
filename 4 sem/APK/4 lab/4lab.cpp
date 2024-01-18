#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
unsigned int delay_time = 0;
unsigned int delay_ms = 0;

int ms;

#define CMOS_TIME_COUNT 6

char data[CMOS_TIME_COUNT];
void interrupt (*__timer_handler_sys)(...);
void interrupt (*__alarm_handler_sys)(...);
unsigned char convert_to_dec(int value);
unsigned char convert_to_bcd(int value);

#define RTC_ALLOW_FLAG 0x80     // 1000 0000
#define RTC_DISALLOW_MASK 0x7f  // 0111 1111

#define RTC_CURRENT_SEC 0x00
//00h: RTC — текущая секунда (00 – 59h или 00 – 3Bh) — формат выбирается регистром 0Bh, по умолчанию — BCD

#define RTC_CURRENT_ALARM_SEC 0x01
//01h: RTC — секунды будильника (00 – 59h или 00 – 3Bh или FFh (любая секунда))

#define RTC_CURRENT_MIN 0x02
//02h: RTC — текущая минута (00 – 59h или 00 – 3Bh)

#define RTC_CURRENT_ALARM_MIN 0x03
//03h: RTC — минуты будильника (00 – 59h или 00 – 3Bh или FFh)

#define RTC_CURRENT_HOUR 0x04
//04h: RTC — текущий час:
//		0 – 23h/00 – 17h (24-часовой режим)
//		1 – 12h/01 – 1Ch (12-часовой режим до полудня)
//		81h – 92h/81 – 8Ch (12-часовой режим после полудня)

#define RTC_CURRENT_ALARM_HOUR 0x05
//05h: RTC — часы будильника (то же или FFh, если любой час)

#define RTC_CURRENT_WEEK_DAY 0x06
//06h: RTC — текущий день недели (1 – 7, 1 — воскресенье)

#define RTC_CURRENT_MONTH_DAY 0x07
//07h: RTC — текущий день месяца (01 – 31h/01h – 1Fh)

#define RTC_CURRENT_MONTH 0x08
//08h: RTC — текущий месяц (01 – 12h/01 – 0Ch)

#define RTC_CURRENT_YEAR 0x09
//09h: RTC — текущий год (00 – 99h/00 – 63h)

#define RTC_STATE_A 0x0A
//0Ah: RTC — регистр состояния А
//		бит 7: 1 — часы заняты (происходит обновление)
//		биты 4 – 6: делитель фазы (010 — 32 768 KHz — по умолчанию)
//		биты 3 – 0: выбор частоты периодического прерывания:
//			0000 — выключено
//			0011 — 122 микросекунды (минимум)
//			1111 — 500 миллисекунд
//			0110 — 976,562 микросекунды (1024 Hz)

#define RTC_STATE_B 0x0b
//0Bh: RTC — регистр состояния В
//		бит 7: запрещено обновление часов (устанавливают перед записью новых значений в регистры даты и часов)
//		бит 6: вызов периодического прерывания (IRQ8)
//		бит 5: вызов прерывания при срабатывании будильника
//		бит 4: вызов прерывания по окончании обновления времени
//		бит 3: включена генерация прямоугольных импульсов
//		бит 2: 1/0 — формат даты и времени двоичный/BCD
//		бит 1: 1/0 — 24-часовой/12-часовой режим
//		бит 0: автоматический переход на летнее время в апреле и октябре

#define RTC_STATE_C 0x0c
//0Ch только для чтения: RTC — регистр состояния С
//		бит 7: произошло прерывание
//		бит 6: разрешено периодическое прерывание
//		бит 5: разрешено прерывание от будильника
//		бит 4: разрешено прерывание по окончании обновления часов

//0Dh только для чтения: регистр состояния D
//		бит 7: питание RTC/CMOS есть


void refresh_time();
void print_time();
void set_time();
void make_delay(unsigned int ms);
void set_alarm();
void enter_new_time();
void change_freq();

void change_freq(){
	int freq;
	int q;
	int bin;
	printf("select frequency: \n");
	printf("1 2 hertz\n");
	printf("2 4 hertz\n");
	printf("3 8 hertz\n");
	printf("4 16 hertz\n");
	printf("5 32 hertz\n");
	printf("6 64 hertz\n");
	printf("7 128 hertz\n");
	printf("8 256 hertz\n");
	printf("9 512 hertz\n");
	printf("10 1024 hertz\n");
	printf("11 2048 hertz\n");
	printf("12 4096 hertz\n");
	printf("13 8192 hertz\n");
	scanf("%d", &q);
	freq = 0x0F - q + 1;

	outp(0x70, RTC_STATE_A);
	bin = inp(0x71);
	printf("frequency set before %X \n", bin);

	outp(0x70, RTC_STATE_A);
	outp(0x71, inp(0x71) & RTC_DISALLOW_MASK); // 1000 0000 (disallow to change)

	outp(0x70, RTC_STATE_A);
	outp(0x71, inp(0x71) & (0x20 + freq)); // 0010 0000 + freq

	outp(0x70, RTC_STATE_A);
	outp(0x71, inp(0x71) | RTC_ALLOW_FLAG); // 0111 1111 (disallow to change)

	outp(0x70, RTC_STATE_A);
	bin = inp(0x71);  //00100110
	printf("\nchanged frequency %X \n", bin);
}

void set_freq(int freq) {
	long base_freq = 1193180;  // внутренняя частота таймера
	long calculated_freq;
	outp(0x43, 0xB6);     //запись в регистр канала канал 2, операция 4, режим работы 3, формат 0
	// 0b10110110

	// формат:
	// bit0   State
	//  0     Двочный
	//  1     Двоично-десятичный

	// режим работы:
	// bit3 bit2 bit1   State
	//  0    0    0     Генерация прерывания IRQ0 при установке счетчика в 0
	//  0    0    1     Установка в режим ждущего мультивибратора
	//  0    1    0     Установка в режим генератора импульсов
	//  0    1    1     Установка в режим генератора прямоугольных импульсов
	//  1    0    0     Установка в режим программно зависимого одновибратора
	//  1    0    1     Установка в режим аппаратно-зависимого одновибратора

	// тип операции:
	// bit5 bit4   State
	//  0    0     Команда блокировки счетчика
	//  0    1     Чтение/запись только младшего байта
	//  1    0     Чтение/запись только старшего байта
	//  1    1     Чтение/запись младшего, а за ним старшего байта

	// выбор канала:
	// bit7 bit6   State
	//  0    0     Выбор первого канала (0)
	//  0    1     Выбор второго канала (1)
	//  1    0     Выбор третьего канала (2)
	//  1    1     Команда считывания значений из регистров каналов
	calculated_freq = base_freq / freq;
	outp(0x42, calculated_freq % 256); // младший байт делителя
	calculated_freq /= 256;
	outp(0x42, calculated_freq);       //старший байт делителя
	return;
}

//функция работы с громкоговорителем
void set_speaker(int is_active) {

//	7	RAM parity error occurred
//	6	I/O channel parity error occurred
//	5	mirrors timer 2 output condition
//	4	toggles with each refresh request
//	3	NMI I/O channel check status
//	2	NMI parity check status
//	1	speaker data status
//	0	timer 2 clock gate to speaker status

	if (is_active) {
		outp(0x61, inp(0x61) | 0x3);    //устанавливаем 2 младших бита в порте динаминка 11
		// 0b00000011
		return;
	} else {
		outp(0x61, inp(0x61) & 0xFC);   //устанавливаем 2 младших бита в порте динаминка 00
		// 0x11111100
		return;
	}
}

void interrupt __new_alarm_handler(...)
{
	outp(0x70, RTC_STATE_C);
	if (inp(0x71) & 0x20) { // interrupt called because of RTC alarm
		printf("ALARM!!!\n");
		set_freq(329);
		set_speaker(1);    //включаем громкоговоритель
		delay(500);         //устанавливаем длительность мс
		set_speaker(0);    //выключаем громкоговоритель
	}
	outp(0x20, 0x20);
	outp(0x0A, 0x20);
	disable(); // CLI
	setvect(0x70, __alarm_handler_sys);
	enable(); // STI
	outp(0x70, RTC_STATE_B);
	outp(0x71, (inp(0x71) & 0xDF));
}

void interrupt __new_timer_handler(...)
{
	outp(0x70, RTC_STATE_C);
	if (inp(0x71) & 0x40) { //0010 1000
		delay_time++;
	}
	outp(0x20, 0x20); // send EOI to Master Interrupt controller
	outp(0xA0, 0x20); // send EOI to Slave Interrupt controller

	if (delay_time == delay_ms) {
		puts("End of delay\n");
		disable(); // CLI
		setvect(0x70, __timer_handler_sys);
		enable(); // STI
		outp(0x70, RTC_STATE_B);
		outp(0x71, (inp(0x71) & 0xBF));
	}
}

unsigned char convert_to_dec(int value)
{
	return (unsigned char) ( ( value / 16 * 10 ) + ( value % 16 ) );
}
unsigned char convert_to_bcd(int value)
{
	return (unsigned char) ( ( value / 10 * 16 ) + ( value % 10 ) );
}

int main()
{
	while (1)
	{
		printf("1 current time\n");
		printf("2 set time\n");
		printf("3 set delay\n");
		printf("4 change freq\n");
		printf("5 set alarm\n");
		printf("6 exit\n");
		switch (getch())
		{
			case '1':
				system("cls");
				refresh_time();
				print_time();
				break;
			case '2':
				system("cls");
				set_time();
				break;
			case '3':
				system("cls");
				fflush(stdin);
				puts("Enter delay in ms: ");
				scanf("%d", &ms);
				make_delay(ms);
				break;
			case '4':
				system("cls");
				change_freq();
				break;
			case '5':
				system("cls");
				set_alarm();
				break;
			case '6':
				system("cls");
				return 0;
			default:
				system("cls");
				puts("Incorrect input!\n");
				break;
		}
	}
}

void refresh_time()
{
	unsigned int time_cmos[] = { RTC_CURRENT_SEC,
								 RTC_CURRENT_MIN,
								 RTC_CURRENT_HOUR,
								 RTC_CURRENT_MONTH_DAY,
								 RTC_CURRENT_MONTH,
								 RTC_CURRENT_YEAR
	};
	for (int i = 0; i < CMOS_TIME_COUNT; i++) {
		outp(0x70, time_cmos[i]);
		data[i] = inp(0x71);
	}
}

int* convert_time_to_dec()
{
	int * converted = (int*)malloc(CMOS_TIME_COUNT * sizeof(int));
	for (int i = 0; i < CMOS_TIME_COUNT; i++) {
		converted[i] = convert_to_dec(data[i]);
	}
	return converted;
}

void print_time()
{
	int * converted = convert_time_to_dec();
	char * format = NULL;
	char * months[] = {
		"Jan", "Feb", "Mar",
		"Apr", "May", "Jun", "Jul",
		"Aug", "Sept", "Oct",
		"Nov", "Dec"
	};
	format = (converted[2] < 10) ? "0%d:" : "%2d:";
	printf(format, converted[2]);
	format = (converted[1] < 10) ? "0%d:" : "%2d:";
	printf(format, converted[1]);
	format = (converted[0] < 10) ? "0%d\n" : "%2d\n";
	printf(format, converted[0]);
	printf("%s, %2d, ", months[converted[4] - 1], converted[3]);
	format = (converted[5] < 10) ? "200%d\n" : "20%2d\n";
	printf(format, converted[5]);
}

void set_time()
{
	enter_new_time();
	disable(); // CLI
	outp(0x70, RTC_STATE_B);

	outp(0x71, inp(0x71) & RTC_DISALLOW_MASK); // запретить обновление часов
	int time_cmos[] = { RTC_CURRENT_SEC, RTC_CURRENT_MIN, RTC_CURRENT_HOUR };

	for (int i = 0; i < 3; i++) {
		outp(0x70, time_cmos[i]);
		outp(0x71, data[i]);
	}
	
	outp(0x71, inp(0x71) | RTC_ALLOW_FLAG); // разрешить обновление часов
	enable(); // STI
}

void make_delay(unsigned int ms)
{
	delay_time = 0;
	delay_ms = ms;
	disable(); // CLI
	__timer_handler_sys = getvect(0x70);
	setvect(0x70, __new_timer_handler);
	outp(0xA1, (inp(0xA0) & 0xFE));
	enable(); // STI
	outp(0x70, RTC_STATE_B);
	outp(0x71, (inp(0x71) | 0x40));
}

void set_alarm()
{
	enter_new_time();
	disable(); // CLI
	__alarm_handler_sys = getvect(0x70);
	setvect(0x70, __new_alarm_handler);
	outp(0xA1, (inp(0xA0) & 0xFE));
	int alarm_cmos[] = { RTC_CURRENT_ALARM_SEC, RTC_CURRENT_ALARM_MIN, RTC_CURRENT_ALARM_HOUR };
	for (int i = 0; i < 3; i++) {
		outp(0x70, alarm_cmos[i]);
		outp(0x71, data[i]);
	}
	enable(); // STI
	outp(0x70, 0x0B);
	outp(0x71, inp(0x71) | 0x20);
	puts("Alarm enabled!\n");
}

int get_value_in_range(int low, int high, char* const instruct)
{
	int value;
	do {
		puts(instruct);
		scanf("%d", &value);
	} while (value > high && value < low);
	return value;
}

void enter_new_time()
{
	int n = get_value_in_range(0, 23, "New hours: ");
	data[2] = convert_to_bcd(n);
	n = get_value_in_range(0, 59, "New minutes");
	data[1] = convert_to_bcd(n);
	n = get_value_in_range(0, 59, "New seconds: ");
	data[0] = convert_to_bcd(n);
}
