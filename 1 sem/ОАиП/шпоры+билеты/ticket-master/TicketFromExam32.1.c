#include <stdio.h>
#include <malloc.h>
int SumIntegers(int** matrix, int size);
int main() {
    int summ = 0;
    int n, k;
    int **matrix;
    printf("Enter a size of matrix: \n");
    scanf_s("%d", &n);
    printf("Enter a values: \n");


    matrix = (int **) calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *) calloc(n, sizeof(int));
        for (int j = 0; j < n; j++) {
            printf("[%d][%d]", i, j);
            scanf_s("%d", &matrix[i][j]);
        }
    }

    printf("Entered matrix\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }

    int sum = SumIntegers(matrix, n);
    printf("\n");
    printf("%d", sum);

    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
    return 0;
}
int SumIntegers(int** matrix, const int size)
{
    static int sum, i = 1, j, counter;
    if (j < size - i)
    {
        j++;
        SumIntegers(matrix, size);
    }
    if (j < size && j >= size - i)
    {
        if (matrix[i][j] % 2 == 0)
        {
            j++;
            SumIntegers(matrix, size);
        }
        else
        {
           sum += matrix[i][j];
           j++;
           counter++;
           SumIntegers(matrix, size);
        }
    }
    if (i < size - 1)
    {
        i++;
        j = 0;
        SumIntegers(matrix, size);
    }
    if (counter == 5 || i == size - 1)
    {
        return sum;
    }
}
