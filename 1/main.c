/*
Составить программу умножения или деления двух чисел, где порядок имеет до 5 знаков: от –99999 до +99999,s
а мантисса – до 30 знаков.
Программа должна осуществлять ввод чисел и 
выдавать либо верный результат в указанном формате (при корректных данных),
либо сообщение о невозможности произвести счет

Смоделировать операцию умножения целого числа длиной до 30 десятичных цифр на действительное число в форме
m.n Е K, где суммарная длина мантиссы (m+n) - до 30 значащих цифр, а величина порядка K - до 5 цифр.
 Результат выдать в форме 0.m1 Е K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30

#define ERROR_NONE 0
#define ERROR_INPUT 1
#define ERROR_MEMORY 2
#define ERROR_ARIPHMETIC 3
#define ERROR_UNDEFINED 4

void input_integer (int *arr, int *size, int *sign, int *error);
void input_float (int *arr, int *size, int *sign, int *exp, int *to_dot, int *error);

void multiplication(int *arr_int, int *arr_float, int *result, int size_int, int size_float, int sign_float, int sign_int, int *exp, int *error);

void normalize_integer (int *arr, int *size);
void normalize_float (int *arr, int *size, int *to_dot, int *exp, int *error);
void shift_to_end (int *arr, int *size, int start_pos);

void print_int (int *arr, int sign, int size);
void print_float (int *arr, int sign, int size, int to_dot, int exp);
void swap_int (int *a, int *b);

int main()
{
    int error_code = ERROR_NONE;

    int *int_arr, *float_arr, *int_res;
    int exp = 0;

    int int_sign = 0, int_size = 0;
    int mant_sign = 0, mant_size = 0;
    int to_dot = 0;

    int_arr = calloc(MAX_N, sizeof(int));
    float_arr = calloc(MAX_N, sizeof(int));
    int_res = calloc(MAX_N * 2, sizeof(int));

    if (int_arr && float_arr && int_res)
    {
        printf("This program will multiply inputed integer and float value\n");
        input_integer (int_arr, &int_size, &int_sign, &error_code);
        if (error_code == ERROR_NONE)
        {
            input_float(float_arr, &mant_size, &mant_sign, &exp, &to_dot, &error_code);
            //printf("to dot: %d\n", to_dot);
            if (error_code == ERROR_NONE)
            {
                normalize_integer(int_arr, &int_size);
                normalize_float(float_arr, &mant_size, &to_dot, &exp, &error_code);

                if (error_code == ERROR_NONE)
                {
                    printf("\nA = ");
                    print_int(int_arr, int_sign, int_size);
                    printf("B = ");
                    print_float(float_arr, mant_sign, mant_size, to_dot, exp);
                    printf("A * B = ");
                    if (error_code == ERROR_NONE);
                        multiplication(int_arr, float_arr, int_res, int_size, mant_size, mant_sign, int_sign, &exp, &error_code);
                }
            }
        }
    }
    else
        error_code = ERROR_MEMORY;

    free(int_arr);
    free(float_arr);
    free(int_res);

    return error_code;
}

void input_integer (int *arr, int *size, int *sign, int *error)
{
    printf("\nInput integer number with up to 30 digits length:\n");
    printf("Correct input examples: 43245, -1620, +9875, 000127\n");
    printf("1        10        20       30\n");
    printf("|--------|---------|---------|\n");

    int num;
    int is_zero = 1;
    *size = 0;

    while((num = getchar()) != EOF && (num != '\n') && *error == ERROR_NONE)
    {
        if (*size > MAX_N - 1)
        {
            printf("Too many characters\n");
            *error = ERROR_INPUT;
            break;
        }

        if (num == '+' || num == '-')
            if (*size > 0 || *sign != 0)
            {
                printf("Wrong input format\n");
                *error = ERROR_INPUT;
                break;
            }
            else
            {
                *sign = num == '+' ? 1 : -1;
                continue;
            }

        if (num < '0' || num > '9')
        {
            printf("Non-digit symbols detected\n");
            *error = ERROR_INPUT;
            break;
        }
        else
        {
            if (num != '0')
                is_zero = 0;
            arr[*size] = (int)num - 48;
            *size = *size + 1;
        }
    }

    if (*size == 0 && *error == ERROR_NONE)
    {
        printf("Empty input");
        *error = ERROR_INPUT;
    }

    if (*sign == 0) // Если знак не введен, то считаем число положительным
        *sign = 1;

    if (is_zero && *error == ERROR_NONE)
    {
        printf("Input should not be 0");
        *error = ERROR_INPUT;
    }
}

//Удаление незначащих нулей из числа
void normalize_integer (int *arr, int *size)
{
    int k = 0;
    for (int i = 0; arr[i] == 0;  k++)
    {
        shift_to_end(arr, size, i);
    }

    *size = *size - k;
}

// Перебрасывание символа с позиции start_pos в конец массива arr
void shift_to_end (int *arr, int *size, int start_pos)
{
    for (int i = start_pos; i < *size - 1; i++)
        swap_int((arr + i),(arr + i + 1));
}

void swap_int (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void input_float (int *arr, int *size, int *sign, int *exp, int *to_dot, int *error)
{
    printf("\nInput float number:\n");
    printf("Correct input examples: 1e0, 1e-2, -3e43, 2.412, .21 \n");
    printf("1        10        20       30e1   5\n");
    printf("|--------|---------|---------|-|---|\n");

    int num;
    int is_zero = 1;
    int is_dot = 0;

    while((num = getchar()) != EOF && (num != '\n') && !(num == 'e' || num == 'E') && *error == ERROR_NONE)
    {
        if (*size > MAX_N - 1) // Контроль за резмером массива
        {
            printf("Input has more than 30 digits\n");
            *error = ERROR_INPUT;
            break;
        }

        if (num == '+' || num == '-')
            if (*size > 0 || *sign != 0)
            {
                printf("Wrong input format\n");
                *error = ERROR_INPUT;
                break;
            }
            else
                *sign = num == '+' ? 1 : -1;
        else if ((num < '0' || num > '9') && num != '.')
        {
            printf("Wrong input format\n");
            *error = ERROR_INPUT;
            break;
        }
        else
        {
            if (num == '.')
                if (is_dot == 1) 
                {
                    printf("Wrong input format\n");
                    *error = ERROR_INPUT;
                    break;
                }
                else
                {
                    is_dot = 1;
                    *to_dot = *size;
                    continue;
                }
            if (num != '0')
                is_zero = 0;
            arr[*size] = (int)num - 48;
            *size = *size + 1;
        }
    }

    if (*size == 0 && *error == ERROR_NONE)
    {
        printf("Empty input\n");
        *error = ERROR_INPUT;
    }

    if (*error == ERROR_NONE)
        if (num == 'e' || num == 'E')
        {
            if (scanf("%d", exp) != 1)
            {
                *error = ERROR_INPUT;
                printf("Wrong exp input\n");
            }

            if (*exp > 99999 || *exp < -99999 && *error == ERROR_NONE)
            {
                printf("Exp should lie between -99999 and 99999\n");
                *error = ERROR_INPUT;
            }
        }
        else if (*size < 1)
        {
            printf("E/e must be presented in number\n");
            *error = ERROR_INPUT;
        }

    if (*sign == 0) // Если знак не введен, то считаем число положительным
        *sign = 1;

    if (is_dot == 0)
        *to_dot = *size;

    if (is_zero && *error == ERROR_NONE)
    {
        printf("Input should not be 0");
        *error = ERROR_INPUT;
    }
}

//Приведение числа к виду M * E^p, где M = [0,1 ; 1), а E = 10, p - целый порядок со знаком
void normalize_float (int *arr, int *size, int *to_dot, int *exp, int *error)
{
    int k = 0;
    int temp = *to_dot;

    for (int i = 0; arr[i] == 0 && k <= temp; k++) // Отбрасывание в конец всех нулей до точки
    {
        shift_to_end(arr, size, i);
        *to_dot = *to_dot - 1;
    }

    for (int i = *size - 1; arr[i] == 0; i--) // Отбрасывание незначащих нулей
        *size = *size - 1;

    if (*to_dot == 0)
    {
        for (int i = k - 1, flag = 0; flag == 0;) // Отбрасывание в экспоненту всех значащих нулей после точки
        {
            if (arr[i+1] != 0)
                flag = 1;

            if (arr[i] != 0)
                break;

            shift_to_end(arr, size, i);
            *exp = *exp - 1;
        }

        for (int i = *size - 1; arr[i] == 0; i--) // Отбрасывание незначащих нулей
            *size = *size - 1;
    }

    *exp = *exp + *to_dot;

}

void multiplication(int *arr_int, int *arr_float, int *result, int size_int, int size_float, int sign_float, int sign_int, int *exp, int *error)
{
    int current;
    int summ_delay = 0;
    int res_size = 0;
    int res_sign;

    if (sign_int == -1)
        res_sign = sign_float == -1 ? 1 : -1;
    else
        res_sign = sign_float == -1 ? -1 : 1;

    for (int i = size_float - 1; i > -1; i--, summ_delay++)
    {
        current = MAX_N * 2 - 1 - summ_delay;
        for (int k = size_int - 1; k > -1; k--)
        {
            result[current] += arr_int[k] * arr_float[i];
            current--;
        }
    }

    res_size = MAX_N*2;
    
    for (int i = res_size - 1; i > 0; i--)
    {
        if (result[i] > 9)
        {
            result[i-1] += result[i] / 10;
            result[i] = result[i] % 10; 
        }
    }

    /*
    printf("\n Unsorted res: ");
    print_int(result, res_sign, res_size);
    printf("\n");
    */

    normalize_integer(result, &res_size);
    
    if (res_size > MAX_N)
    {
        int deletions = 0;
        for (int i = res_size - 1; i > MAX_N - 1; i--, deletions++) // Почисловое округление и выведение лишних чисел в экспоненту
        {
            if (result[i] >= 5)
                result[i-1]++;
            
            res_size--;
            *exp = *exp + 1;
        }

        if (*error == ERROR_NONE)
        {
            int *temp = (int *)realloc(result, res_size * sizeof(int)); // Освобождение излиней памяти

            if (temp)
            {
                result = temp;
                temp = NULL;
            }
            else
            {
                printf("Mem allocation error\n");
                *error = ERROR_MEMORY;
            }
        }
    }
    
    *exp = *exp + (res_size - size_float);

    for (int i = res_size - 1; i > 0; i--)
    {
        if (result[i] > 9)
        {
            result[i-1] += result[i] / 10;
            result[i] = result[i] % 10; 
        }
    }

    for (int i = res_size - 1; result[i] == 0; i--)
        res_size -= 1;

    if (*exp > 99999 || *exp < -99999)
    {
        printf("Maximum value overflow\n");
        *error = ERROR_ARIPHMETIC;
    }

    if (*error == ERROR_NONE)
        print_float(result, res_sign, res_size, 0, *exp);

}

void print_int (int *arr, int sign, int size)
{
    if (sign == -1)
        printf("%c", '-');
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void print_float (int *arr, int sign, int size, int to_dot, int exp)
{
    if (sign == -1)
        printf("%c", '-');

    printf("0.");
    
    for (int i = 0; i < size; i++)
        printf("%d", arr[i]);

    printf("e");
    printf("%d\n", exp);
}