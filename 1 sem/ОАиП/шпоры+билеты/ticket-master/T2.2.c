#include <stdio.h>
#include <malloc.h>
void MultiplyMatrix(int** firstMatrix, int** secondMatrix, int m, int n, int k, int l);
int main()
{
    int n, m, k, l;
    int** firstMatrix;
    int** secondMatrix;
    printf("Enter a size of the first matrix \n");
    printf("Enter a number of strings: \n");
    scanf_s("%d", &n);
    printf("Enter a number of columns: \n");
    scanf_s("%d", &m);

    printf("Enter a size of the second matrix \n");
    printf("Enter a number of strings: \n");
    scanf_s("%d", &k);
    printf("Enter a number of columns: \n");
    scanf_s("%d", &l);

    printf("Enter the first matrix \n");
    firstMatrix = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        firstMatrix[i] = (int*)calloc(m, sizeof(int));
        {
            for (int j = 0; j < m; j++)
            {
                printf("[%d][%d] ", i, j);
                scanf_s("%d", &firstMatrix[i][j]);
            }
        }
    }

    printf("Enter the second matrix \n");
    secondMatrix = (int**)calloc(k, sizeof(int*));
    for (int i = 0; i < k; i++)
    {
        secondMatrix[i] = (int*)calloc(l, sizeof(int));
        {
            for (int j = 0; j < l; j++)
            {
                printf("[%d][%d] ", i, j);
                scanf_s("%d", &secondMatrix[i][j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%5d", firstMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < l; j++)
        {
            printf("%5d", secondMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    MultiplyMatrix(firstMatrix, secondMatrix, m, n, k, l);



    for (int i = 0; i < n; i++)
    {
        free(firstMatrix[i]);
    }
    free(firstMatrix);

    for (int i = 0; i < k; i++)
    {
        free(secondMatrix[i]);
    }

    free(secondMatrix);

    return 0;
}

void MultiplyMatrix(int** firstMatrix, int** secondMatrix, int m, int n, int k, int l)
{
    int a1 = 0, b1 = 0, a2 = 0, b2 = 0; //firstMatrix[a1][b1], secondMatrix[a2][b2]
    int** result; 
    result = (int**)calloc(k, sizeof(int*));
    for (int i = 0; i < k; i++)
    {
        result[i] = (int*)calloc(l, sizeof(int));
    }

    /*for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < l; j++)
        {
            while (b1 < m && a2 < k && b2 < l)
            {
                result[i][j] += firstMatrix[a1][b1] * secondMatrix[b1][j];
                b1++;
            }
            b1 = 0;
        }
        a1++;
    }*/
    int i = 0, j = 0;
    do
    {
        do
        {
            do
            {
                result[i][j] += firstMatrix[a1][b1] * secondMatrix[b1][j];
                b1++;
            } while (b1 < m);
            b1 = 0;
            j++;
        } while (j < l);
        j = 0;
        a1++;
        i++;
    } while (i < k);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < l; j++)
        {
            printf("%5d", result[i][j]);
        }
        printf("\n");
    }
}
