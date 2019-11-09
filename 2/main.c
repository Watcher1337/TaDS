/*
Создать таблицу, содержащую не менее 40-ка записей (тип – запись с вариантами). 
Упорядочить данные в ней по возрастанию ключей, где ключ – любое невариантное поле (по выбору программиста), используя: 
а) саму таблицу, 
б) массив ключей (возможность добавления и удаления записей в ручном режиме обязательна)

Имеются описания:
Type жилье = (дом, общежитие);
Данные:
имя, пол (м, ж), возраст, средний балл за сессию, дата поступления
адрес:
дом : (улица, №дома, №кв );
общежитие : (№общ., №комн.);
Ввести общий список студентов группы.
Вывести список студентов, живущих в общежитии указанного года поступления.

Создать таблицу, содержащую не менее 40 записей с вариантной частью. Произвести поиск информации по вариантному полю.
Упорядочить таблицу, по возрастанию ключей (где ключ – любое невариантное поле по выбору программиста), используя:
а) исходную таблицу; 
б) массив ключей, используя 2 разных алгоритма сортировки. 
Оценить эффективность этих алгоритмов (по времени и по используемому объему памяти) при различной реализации программы, то есть в случаях а) и б). 
Обосновать выбор алгоритма сортировки. Оценка эффективности должна быть относительной (в %).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ERROR_NONE 0
#define ERROR_MEMORY 1
#define ERROR_INPUT 2
#define ERROR_FILE 3

#define MAX_LIST_SIZE 100
#define MAX_AVG_POINTS 310
#define MAX_BUFF_SIZE 256

struct Stud
{
    char name[20];
    char sex[6]; 
    int age;
    int avg_exam_pts;
    char enroll_date[10];

    int flag;

    union Home
    {
        struct Flat
        {
            char street[30];
            int house_num;
            int flat_num;
        } Flat;
        
        struct Hostel
        {
            int hostel_num;
            int flat_num;
        } Hostel;
    };
    
};

struct Keys
{
    int stud_index[MAX_LIST_SIZE]; 
    int value[MAX_LIST_SIZE];
} Keys;

int readFile(FILE *file, struct Stud *students, int *error);
void readTable(struct Stud *students, int *amount, int *error);
void createKeys(struct Stud *students, struct Keys *keys, int size);
void sortKeys(struct Keys *keys, int size);
void printStruct(struct Stud students);
void addEntry(FILE *file, struct Stud *students, int size, int *error);
void deleteEntry(FILE *file, struct Stud *students, int *size);
void display_sorted_table(struct Stud *students, struct Keys Keys, int amount);
void getStudentsByDate(struct Stud *students, int size);
void insert_sort_keys(struct Keys *Keys, int amount);
void insert_sort_full(struct Stud *students, int amount);
void choice_sort_keys(struct Keys *Keys, int amount);
void choice_sort_full(struct Stud students[], int amount);
void analyse_sorts_keys(struct Stud *students, struct Keys Keys, int amount);
void printMenu();
void swap_students(struct Stud *A, struct Stud *B);
void swap_int(int *a, int *b);
int findMaxStud(struct Stud *students, int size, int comp);


int main()
{
    struct Stud students[MAX_LIST_SIZE];
    struct Keys keys;
    int error = ERROR_NONE;
    int amount = 0;
    int keysCreated = 0;

    readTable(students, &amount, &error);

    int choice = 1;
    char waste[MAX_BUFF_SIZE];
    FILE *file;

    while (choice != 0 && error == ERROR_NONE)
    {
        printMenu();
        if (scanf("%d", &choice) != 1)
        {
            system("cls");
            printf("\nWarning: Please enter a valid value\n");
            system("pause");
        }
        else
        {
            switch (choice)
            {
            case 1:
                system("cls");
                readTable(students, &amount, &error);                        
                printf("|        Name        |  Sex  |  Age  |  Avg. Points  |    Date    |        Street        |   House/Hostel #   |   Flat/Room #   |\n");
                printf("|--------------------|-------|-------|---------------|------------|----------------------|--------------------|-----------------|\n");
                for (int i = 0; i < amount; i++)
                    printStruct(students[i]);
                system("pause");
                break;

            case 2:
                system("cls");
                file = fopen("table.txt", "a+");            
                addEntry(file, students, amount, &error);
                readTable(students, &amount, &error);            
                fclose(file);
                break;

            case 3:
                system("cls");
                file = fopen("table.txt", "w+");
                deleteEntry(file, students, &amount);
                readTable(students, &amount, &error);
                fclose(file);
                break; 

            case 4:
                system("cls");
                createKeys(students, &keys, amount);
                    printf("| original index | value |\n");
                    printf("|----------------|-------|\n");
                    for (int i = 0; i < amount; i++)
                        printf("| %14d | %5d |\n", keys.stud_index[i], keys.value[i]);
                keysCreated = 1;
                system("pause");
                break;

            case 5:
                system("cls");
                if (keysCreated)
                    sortKeys(&keys, amount);
                else
                    printf("Warning: you have to create keys first\n");
                system("pause");
                break;

            case 6:
                system("cls");
                if (keysCreated)
                {
                    readTable(students, &amount, &error);                        
                    printf("|        Name        |  Sex  |  Age  |  Avg. Points  |    Date    |        Street        |   House/Hostel #   |   Flat/Room #   |\n");
                    printf("|--------------------|-------|-------|---------------|------------|----------------------|--------------------|-----------------|\n");
                    display_sorted_table(students, keys, amount);
                }
                else
                    printf("Warning: you have to create keys first\n");
                system("pause");
                break;

            case 7:
                system("cls");
                getStudentsByDate(students, amount);
                system("pause");
                break;

            case 8:
                system("cls");
                if (keysCreated)
                    analyse_sorts_keys(students, keys, amount);
                else
                    printf("Warning: you have to create keys first\n");
                system("pause");
                break;
            
            default:
                system("cls");
                if (choice == 0)
                    break;
                else
                {
                    system("cls");
                    printf("You should choose one of the options\n");
                    system("pause");
                    break;
                }
            }
        }

        fseek(stdin, 0, SEEK_END);
    }
    system("cls");

    if (error != ERROR_NONE)
        printf("Error %d\n", error);
    return error;
}

void printMenu()
{
    system("cls");
    printf("Please choose one of the options below: \n");
    printf("1 - Display Table\n");
    printf("2 - Add Entry\n");
    printf("3 - Delete Entry\n");
    printf("4 - Create Keys\n");
    printf("5 - Sort Keys\n");
    printf("6 - Display Table By Keys\n");
    printf("7 - Get Hostel Students By Date\n");
    printf("8 - Sorting Efficiency Compare\n");
    printf("0 - Exit\n");
}

void display_sorted_table(struct Stud *students, struct Keys Keys, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        printStruct(students[Keys.stud_index[i]]);
    }
}

void analyse_sorts_keys(struct Stud *students, struct Keys Keys, int amount)
{
    clock_t timer;
    clock_t timer2;
    double insert_time;
    double choice_time;
    double cur = 0;
    int error;

    readTable(students, &amount, &error);
    createKeys(students, &Keys, amount);

    cur = 0;        

    for (int i = 0; i < 1000; i++)
    {
        createKeys(students, &Keys, amount);
        timer = clock();
        insert_sort_keys(&Keys, amount);
        timer2 = clock();
        cur += timer2 - timer;        
    }

    insert_time = (double)(cur) / CLOCKS_PER_SEC;

    cur = 0;    

    for (int i = 0; i < 1000; i++)
    {
        createKeys(students, &Keys, amount);
        timer = clock();
        choice_sort_keys(&Keys, amount);
        timer2 = clock();
        cur += timer2 - timer;
    }
    choice_time = (double)(cur) / CLOCKS_PER_SEC;

    printf("keys: \n");
    printf("insertion sort time: %lf\n", insert_time);
    printf("choice sort time: %lf\n", choice_time);

    cur = 0;

    for (int i = 0; i < 1000; i++)
        {
            readTable(students, &amount, &error);
            timer = clock();
            insert_sort_full(students, amount);
            timer2 = clock();
            cur += timer2 - timer;
        }
    double insert_time_full = cur / CLOCKS_PER_SEC;

    cur = 0;

    for (int i = 0; i < 1000; i++)
        {
            readTable(students, &amount, &error);
            timer = clock();
            choice_sort_full(students, amount);
            timer2 = clock();
            cur += timer2 - timer;
        }

    double choice_time_full = (double)(cur) / CLOCKS_PER_SEC;
    double compare_insert;

    printf("\nFull Table: \n");
    printf("Insertion sort time: %lf\n", insert_time_full);
    printf("Choice sort time: %lf\n\n", choice_time_full);

    if (insert_time_full > insert_time)
    {
        compare_insert = fabs(insert_time_full - insert_time) / insert_time * 100;
        printf("Insertion sort for full table is %.1lf%% slower than keys\n", compare_insert);
    }
    else
    {
        compare_insert = fabs(insert_time - insert_time_full) / insert_time_full * 100;
        printf("Insertion sort for full table is %.1lf%% faster than keys\n", compare_insert);
    }

    if (choice_time_full > choice_time)
    {
        compare_insert = fabs(choice_time_full - choice_time) / choice_time * 100;
        printf("Choice sort for full table is %.1lf%% slower than keys\n", compare_insert);
    }
    else
    {
        compare_insert = fabs(choice_time - choice_time_full) / choice_time_full * 100;
        printf("Choice sort for full table is %.1lf%% faster than keys\n", compare_insert);
    }

    printf("\n");

    int stud_size = 0;
    for (int i = 0; i < amount; i++)
        stud_size += sizeof(students[i]);

    printf("Memory used (Keys): %d\n", sizeof(Keys));
    printf("Memory used (Full Table): %d\n", stud_size);
    double compare = ((double)stud_size - (double)sizeof(Keys)) / (double)sizeof(Keys) * 100;
    printf("Full table uses %.1lf%% more memory than keys\n\n", compare);
}

void getStudentsByDate(struct Stud *students, int size)
{
    char date[10];
    int is_found = 0;
    printf("Enter date in format DD.MM.YYYY: ");
    scanf("%s", date);
    int equal = 0;
    for (int i = 0; i < size; i++)
        if (strcmp(date, students[i].enroll_date) == 0 && students[i].flag == 0)
        {
            printStruct(students[i]);
            is_found = 1;
        }

    if (is_found == 0)
        printf("No results found\n");
}

void deleteEntry(FILE *file, struct Stud *students, int *size)
{
    int choice;

    printf("choose number of entry from table to be deleted\n");

    for (int i = 0; i < *size; i++)
    {
        printf("| %3d ", i);
        printStruct(students[i]);
    }
    
    if (scanf("%d", &choice) == 1)
    {
        for (int i = choice; i < *size - 1; i++)
            swap_students(&students[i], &students[i + 1]);
        *size = *size - 1;
    }
    else
    {
        printf("Wrong Input\n");
        system("pause");
    }

    for (int i = 0; i < *size; i++)
    {
        if (students[i].flag == 1)
        {
            fprintf(file, "%s %s %d %d %s %d %s %d %d", students[i].name, students[i].sex, students[i].age, students[i].avg_exam_pts, students[i].enroll_date, students[i].flag, students[i].Flat.street, students[i].Flat.house_num, students[i].Flat.flat_num);    
        }
        else
        {
            fprintf(file, "%s %s %d %d %s %d %d %d", students[i].name, students[i].sex, students[i].age, students[i].avg_exam_pts, students[i].enroll_date, students[i].flag, students[i].Hostel.hostel_num, students[i].Hostel.flat_num);
        }

        if (i != *size - 1)
            fprintf(file, "\n");
    }

    system("pause");
}

void swap_students(struct Stud *A, struct Stud *B)
{
    struct Stud temp = *A;
    *A = *B;
    *B = temp;
}

void choice_sort_keys(struct Keys *Keys, int amount)
{
    static int shown = 0;

    int last_sorted = 0;
    while (last_sorted < amount)
    {
        int min2 = (*Keys).value[last_sorted];

        int min_pos = last_sorted;

        for (int i = last_sorted; i < amount; i++)
            if ((*Keys).value[i] < min2)
            {
                min2 = (*Keys).value[i];
                min_pos = i;
            }

        int temp = (*Keys).stud_index[last_sorted];
        (*Keys).stud_index[last_sorted] = (*Keys).stud_index[min_pos];
        (*Keys).stud_index[min_pos] = temp;

        temp = (*Keys).value[last_sorted];
        (*Keys).value[last_sorted] = (*Keys).value[min_pos];
        (*Keys).value[min_pos] = temp;

        last_sorted++;
    }
}

void choice_sort_full(struct Stud students[], int amount)
{
    static int shown = 0;

    int last_sorted = 0;
    while (last_sorted < amount)
    {
        int min = students[last_sorted].avg_exam_pts;

        int min_pos = last_sorted;

        for (int i = last_sorted; i < amount; i++)
            if (students[i].avg_exam_pts < min)
            {
                min = students[i].avg_exam_pts;
                min_pos = i;
            }

        struct Stud temp = students[last_sorted];
        students[last_sorted] = students[min_pos];
        students[min_pos] = temp;

        last_sorted++;
    }
}

void insert_sort_keys(struct Keys *Keys, int amount)
{
    int v, v2;
    int j;

    for (int i = 0; i < amount; i++)
    {
        v2 = (*Keys).value[i];
        v = (*Keys).stud_index[i];
        j = i;

        while ((*Keys).value[j-1] > v2 && j > 0)
        {
            (*Keys).value[j] = (*Keys).value[j-1];
            (*Keys).stud_index[j] = (*Keys).stud_index[j-1];
            j = j-1;
        }

        (*Keys).value[j] = v2;
        (*Keys).stud_index[j] = v;
    }
}

void insert_sort_full(struct Stud *students, int amount)
{
    int v2;
    int j;

    for (int i = 0; i < amount; i++)
    {
        struct Stud temp = students[i];
        v2 = students[i].avg_exam_pts;
        j = i;

        while (students[j-1].avg_exam_pts > v2 && j > 0)
        {
            students[j] = students[j-1];
            j = j-1;
        }

        students[j].avg_exam_pts = v2;
        students[j] = temp;
    }
}

void readTable(struct Stud *students, int *amount, int *error)
{
    FILE *file = fopen("table.txt", "r+");

    if (file)
    {
        *amount = readFile(file, students, error);
        fclose(file);
    }
    else
    {
        printf("ERROR: File opening error\n");
        *error = ERROR_FILE;
    }
}

void addEntry(FILE *file, struct Stud *students, int size, int *error)
{
    if (size == MAX_LIST_SIZE)
    {
        system("cls");
        printf("Table has maximum size, delete entries first\n");
        system("pause");
        *error = ERROR_INPUT;
    }

    if (*error == ERROR_NONE)
    {
        struct Stud adder;

        printf("Please enter: name, sex, age, avg.points, date, flag\n");
        printf("flag should be 1 for Flat and any number for Hostel\n");

        int collector = 0;
        collector += scanf("%s", adder.name);
        collector += scanf("%s", adder.sex);
        collector += scanf("%d", &adder.age);
        collector += scanf("%d", &adder.avg_exam_pts);
        collector += scanf("%s", adder.enroll_date);            
        collector += scanf("%d", &adder.flag);
        if (collector == 6)
        {
            if (adder.flag == 1)
            {
                printf("Flat is selected, please enter street, house num and flat num: \n");
                collector += scanf("%s", adder.Flat.street);
                collector += scanf("%d", &adder.Flat.house_num);
                collector += scanf("%d", &adder.Flat.flat_num);

                if (collector != 9)
                {
                    printf("Wrong input\n");
                    *error = ERROR_INPUT;
                    system("pause");
                }
            }
            else
            {
                printf("Hostel is selected, please enter hostel num and room num: \n");
                collector += scanf("%d", &adder.Hostel.hostel_num);
                collector += scanf("%d", &adder.Hostel.flat_num);

                if (collector != 8)     
                {
                    printf("WronG Input\n");
                    *error = ERROR_INPUT;
                    system("pause");
                }       
            }
        }
        else
        {
            printf("WronG Input\n");
            *error = ERROR_INPUT;
            system("pause");        
        }

        if (*error == ERROR_NONE)
        {
            if (adder.flag == 1)
            {
                printf("\n");
                printStruct(adder);
                fprintf(file, "\n%s %s %d %d %s %d %s %d %d", adder.name, adder.sex, adder.age, adder.avg_exam_pts, adder.enroll_date, adder.flag, adder.Flat.street, adder.Flat.house_num, adder.Flat.flat_num);
                printf("Student added to the list, lives in a Flat\n");
                system("pause");
            }
            else
            {
                printf("\n");
                printStruct(adder);
                fprintf(file, "\n%s %s %d %d %s %d %d %d", adder.name, adder.sex, adder.age, adder.avg_exam_pts, adder.enroll_date, adder.flag, adder.Hostel.hostel_num, adder.Hostel.flat_num);
                printf("Student added to the list, lives in a Hostel\n");
                system("pause");
            }
        }
    }
}

void createKeys(struct Stud *students, struct Keys *keys, int size)
{
    for (int i = 0; i < size; i++)
    {
        (*keys).stud_index[i] = i;
        (*keys).value[i] = students[i].avg_exam_pts;
    }
}

void sortKeys(struct Keys *keys, int size)
{
    insert_sort_keys(keys, size);

    printf("| original index | value |\n");
    printf("|----------------|-------|\n");
    for (int i = 0; i < size; i++)
        printf("| %14d | %5d |\n", (*keys).stud_index[i], (*keys).value[i]);
}

void swap_int(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findMaxStud(struct Stud *students, int size, int comp)
{
    int max = 0;

    for (int i = 0; i < size; i++)
        if ((max < students[i].avg_exam_pts && students[i].avg_exam_pts < comp) || max > comp)
            max = students[i].avg_exam_pts;

    return max;
}

void printStruct(struct Stud students)
{
    printf("| %18s |", students.name);
    printf(" %5s |", students.sex);
    printf(" %5d |", students.age);
    printf(" %13d |", students.avg_exam_pts);
    printf(" %10s |", students.enroll_date);
    if (students.flag == 1)
    {
        printf(" %20s |", students.Flat.street);
        printf(" %18d |", students.Flat.house_num);
        printf(" %15d |\n", students.Flat.flat_num);
    }
    else
    {
        printf(" %20s |", "----------");
        printf(" %18d |", students.Hostel.hostel_num);
        printf(" %15d |\n", students.Hostel.flat_num);
    }
}

int readFile(FILE *file, struct Stud *students, int *error)
{
    int amount = 0;
    int counter = 2;

    for (int i = 0; !feof(file); i++, amount++, counter++)
    {
        if (fscanf(file, "%s %s %d %d %s %d", students[i].name, students[i].sex, &students[i].age, &students[i].avg_exam_pts, students[i].enroll_date, &students[i].flag) == 6)
        {
            if (students[i].flag == 1)
            {
                if (fscanf(file, "%s %d %d", students[i].Flat.street, &students[i].Flat.house_num, &students[i].Flat.flat_num) != 3)
                {
                    printf("Error: File reading error\n");
                    *error = ERROR_FILE;
                    break;
                }
            }
            else
                if (fscanf(file, "%d %d", &students[i].Hostel.hostel_num, &students[i].Hostel.flat_num) != 2)
                {
                    printf("Error: File reading error\n");
                    *error = ERROR_FILE;
                    break;   
                }
        }
        else if (!feof(file))
        {
            printf("Error: file reading error\n");
            *error = ERROR_FILE;
            break;
        }
    }
    return amount;
}