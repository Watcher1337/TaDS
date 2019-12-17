#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ERROR_NONE 0
#define ERROR_ERROR 1
#define ERROR_INPUT 2
#define ERROR_ALLOC 3

typedef struct sparse_matrix* s_matrix;
typedef struct sparse_matrix* s_vector;
typedef struct list_node* node_ptr;

struct sparse_matrix
{
    int* A;
    int* JA;
    node_ptr IA;
};

struct list_node
{
    int Nk;
    node_ptr next;
};

int alloc_matrix(int ***matrix, int rows, int columns);
int alloc_vector(int **vector, int size);
void fill_matrix_manually(int **matrix, int rows, int columns);
void fill_vector_manually(int *vectir, int size);
void fill_matrix_auto(int **matrix, int rows, int columns, int percentage);
void fill_vector_auto(int *vector, int size);
void free_matrix(int ***matrix, int rows, int columns);
void transpose_matrix(s_matrix sm, int nze, int **matrix, int rows, int columns);
void free_vector(int **vector);

int alloc_list(node_ptr *list);
int add_element(node_ptr list, int Nk);
node_ptr get_element(node_ptr start, int position);
void remove_element(node_ptr list);
node_ptr get_last(node_ptr list);
void free_sparse(s_matrix *sm);
void empty_list(node_ptr list);

void count_non_zero(int **matrix, int rows, int columns, int *nze);
int calculate_multiplication(int **matrix, int rows, int columns, int nze, s_matrix *sm);
int calculate_multiplication_speed(int rows, int columns);

int alloc_sparse(s_matrix *sm, int nze);
void copy_sparse(s_matrix source, s_matrix destination, int nze);
int convert_matrix(int **matrix, int rows, int columns, s_matrix *sm);
void classic_multiplication(int **matrix, int rows, int columns, int *vector, int *res, int size, int res_size);
void sparse_multiplication(s_matrix sm, int *vector, int *res, int nze, int rows);
void sparse_multiplication_speed(s_matrix sm, int *vector, int *res, int nze, int rows);

void print_error(int error);
void print_sparse_matrix(s_matrix *sm, int nze);
void print_matrix(int **matrix, int rows, int columns);
void print_vector(int *vectot, int size);
void print_list(node_ptr head);

int main()
{
    srand(time(NULL));
    int error = ERROR_NONE;
    
    s_matrix matrix_s;
    int **matrix;
    int rows, columns;
    int percentage = 40;

    printf("Input matrix size: ");
    if (scanf("%d", &columns) == 1 && columns > 0)
    {  
        rows = columns;
        error = alloc_matrix(&matrix, rows, columns);

        if (!error)
        {
            char choice;
            if (rows < 20)
            {
                printf("would you like to fill matrix manually? y/N\n");


                do choice = getchar();
                while (choice == '\n' || choice == EOF);
            }
            else
                choice = 'n';

            if (choice == 'y' || choice == 'Y')
                fill_matrix_manually(matrix, rows, columns);
            else
                fill_matrix_auto(matrix, rows, columns, percentage);
        }

        if (!error)
        {
            if (rows < 20 && columns < 20)
            {
                printf("current matrix: \n");
                print_matrix(matrix, rows, columns);
            }

            int non_zero_el;
            count_non_zero(matrix, rows, columns, &non_zero_el);

            error = alloc_sparse(&matrix_s, non_zero_el);

            if (!error)
                error = convert_matrix(matrix, rows, columns, &matrix_s);

            if (!error)
            {
                if (rows < 20 && columns < 20)
                {
                    printf("\nsparse form:\n");
                    print_sparse_matrix(&matrix_s, non_zero_el);
                    printf("\n");
                    calculate_multiplication(matrix, rows, columns, non_zero_el, &matrix_s);
                }

                int flag = 0;
                char choice;

                while (!flag)
                {
                    calculate_multiplication_speed(rows, columns);
                    fflush(stdin);
                    fseek(stdin, SEEK_END, 0);
                    printf("do you want to continue testing? y/N\n");

                    do choice = getchar();
                    while (choice == '\n' || choice == EOF || choice == ' ');

                    if (choice != 'y' && choice != 'Y')
                        flag = 1;
                }

                free_sparse(&matrix_s);
            }
        }
    }
    else
        error = ERROR_INPUT;


    free_matrix(&matrix, rows, columns);
    
    print_error(error);
    
    return error;
}

//---------------------------------------------------------------------------

int alloc_matrix(int ***matrix, int rows, int columns)
{
    int error = ERROR_NONE;

    (*matrix) = (int **)malloc(sizeof(int *) * rows);

    if ((*matrix))
        for (int i = 0; i < rows && error == ERROR_NONE; i++)
        {
            (*matrix)[i] = (int *)calloc(columns, sizeof(int));

            if (!(*matrix)[i])
                error = ERROR_ALLOC;
        }
    else
        error = ERROR_ALLOC;

    return error;
}

void free_matrix(int ***matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
        free((*matrix)[i]);
    free((*matrix));
}

int alloc_vector(int **vector, int size)
{
    int error = ERROR_NONE;

    (*vector) = (int *)calloc(size, sizeof(int));

    if (!(*vector))
        error = ERROR_ALLOC;

    return error; 
}

void free_vector(int **vector)
{
    free((*vector));
}

void fill_matrix_manually(int **matrix, int rows, int columns)
{
    int i = 0, j = 0, Nk = 0;
    do
    {
        if (i >= 0 && j >= 0 && i < rows && j < columns)
            matrix[i][j] = Nk;
        else
            printf("wrong input\n");

        printf("Enter [i j Nk]: ");
    }
    while (scanf("%d%d%d", &i, &j, &Nk) == 3);
}

void fill_vector_manually(int *vector, int size)
{
    int i = 0, Nk = 0;
    
    do
    {
        if (i >= 0 && i < size)
            vector[i] = Nk;
        else
            printf("wrong position\n");
        
        printf("input [position Nk]: ");
    }
    while (scanf("%d%d", &i, &Nk) == 2);
}

void fill_matrix_auto(int **matrix, int rows, int columns, int percentage)
{
    int chance;
    int filling = rows * columns * percentage / 100;
    int counter = 0;

    while (counter < filling)
    {
        for (int i = 0; i < rows; i++)
            for (int k = 0; k < columns; k++)
            {
                chance = rand() % 100;
                if (chance >= percentage)
                    matrix[i][k] = 0;
                else
                {
                    matrix[i][k] = rand() % 9 + 1;
                    counter++;
                }
            }
    }

    printf("\n");
    if (rows < 40 && columns < 40)
        print_matrix(matrix, rows, columns);
    printf("\n");
}

void fill_vector_auto(int *vector, int size)
{
    for (int i = 0; i < size; i++)
        vector[i] = rand() % 10;
}

//---------------------------------------------------------------------------

int alloc_list(node_ptr *list)
{
    int error = ERROR_NONE;
    
    (*list) = (node_ptr)malloc(sizeof(struct list_node));

    if (!(*list))
        error = ERROR_ALLOC;
    else
        (*list)->next = NULL;

    return error;
}

int add_element(node_ptr list, int Nk)
{
    int error = ERROR_NONE;

    node_ptr last = get_last(list);

    node_ptr temp;
    temp = (node_ptr)malloc(sizeof(struct list_node));

    if (temp)
    {
        temp->Nk = Nk;

        last->next = temp;
        last->next->next = NULL;

        temp = NULL;
    }
    else
        error = ERROR_ALLOC;

    return error;
}

node_ptr get_element(node_ptr start, int position)
{
    int counter = 0;
    while (counter < position && start->next != NULL)
    {
        start = start->next;
        counter++;
    }

    return start;
}

void remove_element(node_ptr list)
{
    node_ptr tmp;
    if (!(list->next == NULL))
    {
        node_ptr last = list;
        while (last->next != NULL)
        {
            tmp = last;
            last = last->next;
        }

        tmp->next = NULL;
        tmp = NULL;
        free(last);
    }
    else
        printf("removing element from empty list...\n");
}

node_ptr get_last(node_ptr list)
{
    while (list->next != NULL)
        list = list->next;

    return list;
}

void empty_list(node_ptr list)
{
    while (list->next != NULL)
        remove_element(list);
}

//---------------------------------------------------------------------------

int alloc_sparse(s_matrix *sm, int nze)
{
    int error = ERROR_NONE;
    *sm = (s_matrix)malloc(sizeof(struct sparse_matrix));
    if (*sm)
    {
        error = alloc_vector(&(*sm)->A, nze);
        if (!error)
            error = alloc_vector(&(*sm)->JA, nze );
        if (!error)
            error = alloc_list(&(*sm)->IA);
    }
    else
        error = ERROR_ALLOC;

    return error;
}

void free_sparse(s_matrix *sm)
{
    free((*sm)->A);
    free((*sm)->JA);
    empty_list((*sm)->IA);
    free((*sm)->IA);
}

int convert_matrix(int **matrix, int rows, int columns, s_matrix *sm)
{
    int error = ERROR_NONE;

    int current = 0;
    int prev_amount = 0;
    int is_first;

    for (int i = 0; i < rows && error == ERROR_NONE; i++)
    {
        is_first = 1;
        for (int k = 0; k < columns; k++)
        {
            if (matrix[i][k] != 0)
            {
                (*sm)->A[current] = matrix[i][k];
                (*sm)->JA[current] = k;

                if (is_first)
                {
                    add_element((*sm)->IA, current);
                    is_first = 0;
                }
                current++;
            }
        }
    }

    add_element((*sm)->IA, current);

    return error;
}

void count_non_zero(int **matrix, int rows, int columns, int *nze)
{
    *nze = 0;

    for (int i = 0; i < rows; i++)
        for (int k = 0; k < columns; k++)
        {
            if (matrix[i][k] != 0)
            {
                *nze = *nze + 1;
            }
        }
}

void classic_multiplication(int **matrix, int rows, int columns, int *vector, int *res, int size, int res_size)
{
    for (int i = 0; i < columns; i++)
        for (int k = 0; k < rows; k++)
            res[i] += matrix[k][i] * vector[k];
}

void copy_sparse(s_matrix source, s_matrix destination, int nze)
{
    for (int i = 0; i < nze; i++)
    {
        destination->A[i] = source->A[i];
        destination->JA[i] = source->JA[i];
    }

    empty_list(destination->IA);
    node_ptr head = source->IA->next;

    while (head)
    {
        add_element(destination->IA, head->Nk);
        head = head->next;
    }
}

void transpose_matrix(s_matrix sm, int nze, int **matrix, int rows, int columns)
{
    int **tmp_matrix;
    int tmp_rows = columns, tmp_columns = rows;
    alloc_matrix(&tmp_matrix, tmp_rows, tmp_columns);

    for (int i = 0; i < rows; i++)
        for (int k = 0; k < columns; k++)
            tmp_matrix[k][i] = matrix[i][k];

    s_matrix tmp_sm;
    alloc_sparse(&tmp_sm, nze);
    convert_matrix(tmp_matrix, tmp_rows, tmp_columns, &tmp_sm);
    copy_sparse(tmp_sm, sm, nze);

    free_matrix(&tmp_matrix, tmp_rows, tmp_columns);
    free_sparse(&tmp_sm);
}

void sparse_multiplication(s_matrix sm, int *vector, int *res, int nze, int rows)
{
    for (int i = 1; i <= rows; ++i) 
        for (int j = get_element(sm->IA, i)->Nk; j < get_element(sm->IA, i + 1)->Nk; j++)
            res[i - 1] += sm->A[j] * vector[sm->JA[j]];
}

void sparse_multiplication_speed(s_matrix sm, int *vector, int *res, int nze, int rows)
{
    time_t timer1, timer2;
    double time = 0;

    for (int i = 1; i <= rows; ++i)
    {

        timer1 = clock();
        int a = get_element(sm->IA, i)->Nk;
        int b = get_element(sm->IA, i + 1)->Nk;
        for (int j = a; j < b; j++)
            res[i - 1] += sm->A[j] * vector[sm->JA[j]];
        timer2 = clock();

        time += (double)(timer2 - timer1) / CLOCKS_PER_SEC;
    }

    printf("--time: %lf\n", time);
}

int calculate_multiplication(int **matrix, int rows, int columns, int nze, s_matrix *sm)
{
    int error = ERROR_NONE;
    s_vector sv, sres;
    int *vector, *res;
    int size = rows;
    int size_res = rows;

    error = alloc_vector(&vector, size);

    if (error == ERROR_NONE)
    {
        printf("do you want to input vector manually? y/N\n");
        char ch;
        
        do ch = getchar();
        while (ch == '\n' || ch == EOF);

        if (ch == 'y' || ch == 'Y')
            fill_vector_manually(vector, size);
        else
            fill_vector_auto(vector, size);

        printf("\nstring-vector: ");
        print_vector(vector, size);
        printf("\n");
    }

    error = alloc_vector(&res, size_res);

    if (error == ERROR_NONE)
    {
        int vec_nze = 0, res_nze = 0;
        count_non_zero(&vector, 1, size, &vec_nze);
        alloc_sparse(&sv, vec_nze);
        convert_matrix(&vector, 1, size, &sv);
        printf("\nin sparse form: \n");
        print_sparse_matrix(&sv, vec_nze);

        classic_multiplication(matrix, rows, columns, vector, res, size, size_res);
        printf("\nclassic multiplication: ");
        print_vector(res, size);
        printf("\n");

        for (int i = 0; i < rows; i++)
            res[i] = 0;
        
        printf("\nsparse multiplication: \n");

        transpose_matrix(*sm, nze, matrix, rows, columns);
        
        sparse_multiplication(*sm, vector, res, nze, rows);
        count_non_zero(&res, 1, size, &res_nze);
        alloc_sparse(&sres, res_nze);
        convert_matrix(&res, 1, size, &sres);
        print_sparse_matrix(&sres, res_nze);
        printf("\n");

        free_vector(&res);
        free_vector(&vector);
    }

    return error;
}

int calculate_multiplication_speed(int rows, int columns)
{
    int **matrix;
    int *vector, *res;
    s_matrix sm;
    s_vector sv;

    int nze = 0;
    int nze_vec = 0;

    clock_t time1;
    clock_t time2;
    double time;

    alloc_matrix(&matrix, rows, columns);
    
    char choice;
    printf("Do you want to input matrix manually? y/N\n");

    do choice = getchar();
    while (choice == '\n' || choice == EOF);

    if (choice == 'y' || choice == 'Y')
        fill_matrix_manually(matrix, rows, columns);
    else
    {
        printf("Enter fill %% of the matrix: ");
        int perc;
        if (scanf("%d", &perc) == 1)
            fill_matrix_auto(matrix, rows, columns, perc);
        else
            printf("wrong input\n");
    }

    count_non_zero(matrix, rows, columns, &nze);
    alloc_sparse(&sm, nze);
    convert_matrix(matrix, rows, columns, &sm);

    alloc_vector(&vector, rows);
    alloc_vector(&res, rows);

    fill_vector_auto(vector, rows);

    printf("classic multiplication: \n");
    printf("--time: ");
    time1 = clock();
    classic_multiplication(matrix, rows, columns, vector, res, rows, rows);
    time2 = clock();
    time = (double)(time2 - time1) / CLOCKS_PER_SEC;
    printf("%lf\n", time);


    long int mem = sizeof(int *) * rows + sizeof(int) * (rows * columns);
    printf("--memory: %ld\n\n", mem);

    for (int i = 0; i < rows; i++)
        res[i] = 0;

    printf("sparse multiplication: \n");
    sparse_multiplication_speed(sm, vector, res, nze, rows);
    mem = sizeof(int) * nze * 2 + sizeof (sm);

    for (node_ptr tmp = sm->IA; tmp != NULL; tmp = tmp->next)
        mem += sizeof(tmp);

    printf("--memory: %ld\n", mem);

    printf("\n\n");

    free_vector(&res);
    free_vector(&vector);
    free_sparse(&sm);
    free_matrix(&matrix, rows, columns);
}


//---------------------------------------------------------------------------

void print_error(int error)
{
    switch(error)
    {
        case ERROR_NONE:
            printf("OK\n");
            break;
        case ERROR_INPUT:
            printf("Input error\n");
            break;
        case ERROR_ALLOC:
            printf("Allocation error\n");
            break;
        case ERROR_ERROR:
            printf("Error other\n");
            break;
        default:
            break;
    }
}

void print_matrix(int **matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < columns; k++)
        {
            printf("%d ", matrix[i][k]);
        }

        printf("\n");
    }
}

void print_vector(int *vector, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", vector[i]);
}

void print_sparse_matrix(s_matrix *sm, int nze)
{
    printf("A: ");
    for (int i = 0; i < nze; i++)
        printf("%d ", (*sm)->A[i]);
    printf("\nJA: ");
    for (int i = 0; i < nze; i++)
        printf("%d ", (*sm)->JA[i]);
    printf("\nIA: ");
    print_list((*sm)->IA);
}

void print_list(node_ptr head)
{
    if (!head->next)
    {
        printf("empty list\n");
    }
    else
    {
        head = head->next;
        while (head != NULL)
        {
            printf("%d ", head->Nk);
            head = head->next;
        }

        printf("\n");
    }
}

//---------------------------------------------------------------------------