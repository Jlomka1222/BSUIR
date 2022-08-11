    #define _CRT_SECURE_NO_WARNINGS 
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct _Film 
    {
        char name[50];
        char category[50];
        int released;
    } Film;

    typedef struct _FilmsInfo 
    {
        int filmsCount;
        int arraySize;
        Film* array;
    } FilmsInfo;

    int getInt(void) 
    {
        int res = 0;
        int chs = 0;
        do {
            res = scanf_s("%d", &chs);
            while (getchar() != '\n');
            if (!res || chs < 0) printf("Wrong input.\n");

        } while (chs < 0 || res != 1);
        return chs;
    }

    void addFilm(FilmsInfo* FI) 
    {
        if (FI[0].arraySize == 0) {
            FI[0].array = (Film*)calloc(1, sizeof(Film));
            if (!FI[0].array) {
                printf("Failed to allocate the memory.");
                _Exit(-1);
            }
            FI[0].arraySize += 1;
        }
        else {
            FI[0].array = (Film*)realloc(FI[0].array, sizeof(Film) * ++FI[0].arraySize);
            if (!FI[0].array) {
                printf("Failed to allocate the memory.");
                _Exit(-1);
            }
        }

        printf("\t\t\t***Ввод новой записи***\n\n");
        printf("Введите название фильма:");
        rewind(stdin);
        while (!scanf("%s", FI[0].array[FI[0].filmsCount].name)) {
            printf("Ошибка ввода!");
        }

        printf("Введите категорию фильма:");
        rewind(stdin);
        while (!scanf("%s", FI[0].array[FI[0].filmsCount].category)) {
            printf("Ошибка ввода!");
        }

        printf("Введите год выпуска фильма:");
        rewind(stdin);
        while (!scanf("%d", &FI[0].array[FI[0].filmsCount].released)) {
            rewind(stdin);
            printf("Ошибка ввода!");
            printf("Введите год выпуска фильма:");
        }

        FI[0].filmsCount = FI[0].filmsCount + 1;
    }

    void displayTable(FilmsInfo* FI)
    {
    
        printf("\t\t\t***Информация о фильмах***\n\n");
        printf("____________________________________\n");
        printf("|№|Название| Категория| Год выпуска|\n");
        printf("|_|________|__________|____________|\n");

        for (int i = 0; i < FI[0].filmsCount; i++) {
        
                printf("|%d|   %5s|     %5s|        %d|\n", i + 1, FI[0].array[i].name, FI[0].array[i].category, FI[0].array[i].released);
                printf("|_|________|__________|____________|\n");
       
        }
        if (FI[0].filmsCount == 0)
        {
            printf("Информация еще не введена!\n");
        }
    }

    void writeFile(FilmsInfo* FI, FILE** file, char* argv[]) 
    {
        fclose(*(file));
        *(file)=fopen(argv[1], "wb+");
        rewind(*(file));
        fwrite(FI[0].array, sizeof(Film), FI[0].filmsCount, *(file));
    }

    void deleteFilm(FilmsInfo* FI)
    {
        char name[50];
        do {
            printf("Type name of the film you want to delete: ");
        } while (!scanf(" %s", name));
        printf("\n%s\n", name);

        for (int i = 0; i < FI[0].filmsCount; i++) {
            printf("Checking %d", i + 1);
            if (!strcmp(name, FI[0].array[i].name)) {
                for (int j = i; j < FI[0].filmsCount - 1; j++) {
                    FI[0].array[j] = FI[0].array[j + 1];
                }
                --FI[0].filmsCount;
                --FI[0].arraySize;
                FI[0].array = (Film*)realloc(FI[0].array, FI[0].filmsCount * sizeof(Film));
                return;
            }
        }
        printf("\nCouldn't find this name.\n");
    }

    void menu(char** argv, FilmsInfo* FI, FILE** file) 
    {
        int command; 
        while (1) {
            printf("\t\t\t***Главное меню***\n\n");
            printf("Выберите операцию:\n");
            printf("1)Добавление фильма\n");
            printf("2)Удаление фильма из списка\n");
            printf("3)Вывод списка фильмов на экран\n");
            printf("4)Сохранить и выйти\n");
            printf("5)Выйти без сохранения.\n");
            command = getInt(); 
            switch (command) {
            case(1):
                rewind(stdin); 
                system("cls");
                addFilm(FI);
                break;
            case(2):
                rewind(stdin); 
                system("cls");
                deleteFilm(FI);
                break;
            case(3):
                rewind(stdin); 
                system("cls");
                displayTable(FI);
                break;
            case(4):
                writeFile(FI, file, argv);
                return;
            case(5):
                printf("Программа завершена без сохранений!");
                return;
            default:
                printf("Выбор сделан неправильно!\n");
                break;
            }
        }
    }

    FilmsInfo getFilmsInfo() 
    {
        FilmsInfo newFilmsInfo;
        newFilmsInfo.filmsCount = 0;
        newFilmsInfo.arraySize = 0;
        return newFilmsInfo;
    }

    void doBackup(FILE* backup, FILE* file) 
    {
        if (!file || !backup) {
            printf("\nFailed to pass file to a function.\n");
            _Exit(-1);
        }
        rewind(file);
        rewind(backup);
        char toTransfer;
        while ((toTransfer = getc(file)) != EOF) 
        {
            putc(toTransfer, backup);
        }
    }

    void copyFilms(FilmsInfo* FI, FILE* file) 
    {
        rewind(file);
        fseek(file, 0L, SEEK_END);
        int fileSize = ftell(file);
        FI[0].array = (Film*)calloc(1, fileSize);
        if (!FI[0].array) _Exit(-1);
        FI[0].arraySize = fileSize / sizeof(Film);
        FI[0].filmsCount = FI[0].arraySize;
        rewind(file);
        fread(FI[0].array, 1, fileSize - 1, file);
    }

    int main(int argc, char* argv[])
    {
        setlocale(0 , "RUS");
        system("color 70");
        system("mode 150,35");
        if (argc<2)
        {
            printf("Ничего не введено в командную строку!");
            return -1;
        }
        FILE* file;
        FILE* backup;
        FilmsInfo filmsInfo = getFilmsInfo();
        file= fopen(argv[1], "a+b");
        backup=fopen("backup", "wb");
        if (!file || !backup) {
            printf("Ошибка открытия файла!");
            return -1;
        }
        copyFilms(&filmsInfo, file);
        doBackup(backup, file);
        fclose(backup);
        menu(argv, &filmsInfo, &file);
        free(filmsInfo.array);
        fclose(file);
        return 0;
    }