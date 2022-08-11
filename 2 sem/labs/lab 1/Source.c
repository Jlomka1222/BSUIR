#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct person
{
	struct 
	{
		char* surname;
		char* name;
		char* secondname;
		int sem;
	};
	union
	{
		int ex[3];
		int res[8][3];
	} semestr;
};

char* exam[8][3] = {
   "LAiAg","ikg","ailocy",
   "MA","oaip","eng",
   "phy","dm","his",
   "TViMS","TEC","BJC",
   "OSV","AWP","SXD",
   "BD","OZI","APT",
   "COSI","FP","OS",
   "OKS","MARK","KDS"
};
int vvodcol()
{
	int kol_st;
	printf("vvedite kolichestvo studentov:");
	while (!(scanf_s("%d", &kol_st)))
	{
		printf("oshibka!");
	}
	if (kol_st < 1)
	{
		printf("kolichstvo vvedeno neverno!");
	}
	return kol_st;
}
int coml(char* argv[])
{
	int kol_st = 0;
	if (argv[1] == NULL)
	{
		return vvodcol();
	}
	else
	{
		for (int i = 0; i < strlen(argv[1]); i++)
		{
			if (argv[1][i] < '0')
			{
				printf("oshibka!!!");
				return -1;
			}
			else
			{
				kol_st = kol_st + argv[1][i] - '0';
				kol_st *= 10;
			}
		}
		kol_st = kol_st / 10;
	}
	
}

int semvvod()
{
	int sem;
	printf("Vvedite nomer semestra:");
	while (!scanf_s("%d", &sem))
	{
		printf("oshibka!");
		return -1;
	};
	if (sem<1 || sem>8)
	{
		printf("nepravilno vveden nomer semestra!\n");
		return semvvod();
	}
	return sem;
}
void studvvod(struct person student)
{
	printf("vvedite familiu studenta:");
	rewind(stdin);
	fgets(student.surname, 40, stdin);
	printf("vvedite imya studenta:");
	fflush(stdin);
	fgets(student.name, 40, stdin);
	printf("vvedite otchestvo studenta:");
	fflush(stdin);
	fgets(student.secondname, 40, stdin);	
}
void studocenka(struct person* student, int index)
{
	int o;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("vvedite ocenku [%d][%d]", i, j);
			while (!scanf_s("%d", &o))
			{
				printf("oshibka!");
			}
			if (o < 0 || o > 10)
			{
				printf("Ocenka vvedena nepravilno!\n");
				printf("vvedite ocenku [%d][%d]", i, j);
				scanf_s("%d", &o);

			}
			student[index].semestr.res[i][j]=o;
		}
	}
}
void inputExams(struct person* student, int index) {
	for (int i = 0; i < 3; ++i) {
		student[index].semestr.ex[i] = i;
	}
}

void studvivod(struct person* student, int kol_st, char* surname)
{
	int arr[3];
	int buff[3];	
	for (int i = 0; i < kol_st; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[j] = student[i].semestr.res[student[i].sem - 1][j];
			buff[j] = student[i].semestr.res[0][j];
		}
		int isEqual = 1;
		for (int k = 0; k < strlen(surname); k++) 
		{
			if (student[i].surname[k] != surname[k]) {
				isEqual = 0;
				break;
			}
		}
		if (isEqual) 
		{
			printf("informaciya o studente :\n");
			printf("Familiya studenta: %s", student[i].surname);
			printf("Imya studenta: %s", student[i].name);
			printf("otchestvo studenta: %s", student[i].secondname);
			printf("nomer semestra: %d\n", student[i].sem);
			inputExams(student, i);
			printf("ekzameni: ");
			for (int j = 0; j < 3; ++j)
			{
				printf("[%s] ", exam[student[i].sem - 1][student[i].semestr.ex[j]]);
			}
			printf("\nocenki: ");
			for (int j = 0; j < 3; ++j)
			{
				printf("%d  ", arr[j]);
				student[i].semestr.res[0][j] = buff[j];
			}
			printf("\n\n");
		}
	}
}
int main(int argc, char* argv[])
{
	system("color F0");
	int index = 0;
	int kol_st; //kolihestvo studentov
	kol_st = coml(argv);
	if (kol_st < 1)
	{
		printf("kolichestvi vvedeno nepravino!");
		kol_st = coml(argv);
	}
	int semes;
	semes = semvvod();
	struct person* student = NULL;
	student = (struct person*)calloc(30, sizeof(struct person));
	for (int i = 0; i < kol_st; i++)
	{
		student[i].surname = (char*)calloc(40, sizeof(char));
		student[i].name = (char*)calloc(40, sizeof(char));
		student[i].secondname = (char*)calloc(40, sizeof(char));
		student[i].sem = semes;
	}
	if (!student)
	{
		printf("Voznikla oshibka pri vidilenii pamyati! Error");
		return -1;
	}
	for (int i = 0; i < kol_st; i++)
	{
		studvvod(student[index]);
		studocenka(student, index);
		index++;
	}
	studvivod(student, kol_st, argv[2]);
	return 0;
	_getch();
}
