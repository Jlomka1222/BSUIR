#include <stdio.h>
#include <malloc.h>
int main()
{
    int n, m;
    int jMin = 0, point = 0;
    int max = 0, min = 0;
    int** matrix;
    printf("Enter a size of the first matrix \n");
    printf("Enter a number of strings: \n");
    scanf_s("%d", &n);
    printf("Enter a number of columns: \n");
    scanf_s("%d", &m);

    matrix = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int*)calloc(m, sizeof(int));
        {
            for (int j = 0; j < m; j++)
            {
                printf("[%d][%d] ", i, j);
                scanf_s("%d", &matrix[i][j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    } 

    printf("\n");
    
    int i = 0, j = 0, k = 0;
    min = matrix[i][j];
    max = matrix[i][j];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m - 1; j++)
        {
            if (matrix[i][j] < min)
            {
                min = matrix[i][j];
                jMin = j;
            }
            /*if (matrix[i][j] > matrix[i][0])
            {
            }*/
            /*else
            {
                min = matrix[i][j + 1];
                jMin = j + 1;
            }*/
        }

        while (k < n - 1)
        {
            if (matrix[k][jMin] > max)
            {
                max = matrix[k][jMin];
            }
            k++;
        }

        if (min == max)
        {
            point = 1;
            printf("The first point is %d\n", min);
            continue;
        }

    }

    if (point == 0)
    {
        printf("There is no point");
    }



    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }

    free(matrix);

    return 0;
}
