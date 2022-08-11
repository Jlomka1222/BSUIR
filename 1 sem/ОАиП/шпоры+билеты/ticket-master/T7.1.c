#include <stdio.h>
#include <stdlib.h>

void sort(int** array, int rows, int startSort, int endSort);
int main()
{
    int** array;
    int n, m;
    printf("Enter the number of rows in the matrix: ");
    scanf_s("%d", &n);
    printf("Enter the number of columns in the matrix: ");
    scanf_s("%d", &m);

    if (!(array = (int**)calloc(n, sizeof(int*)))) return 1;

    for (int i = 0; i < n; i++)
    {
        if (!(array[i] = (int*)calloc(m, sizeof(int)))) return 1;
    }
    printf("\nInitialize the matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf_s("%d", &array[i][j]);
        }
    }
    printf("\nYour matrix:\n\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\t%d", array[i][j]);
        }
        printf("\n");
    }

    int endstr, startstr;
    rewind(stdin);
    printf("Start sort: ");
    scanf_s("%d", &startstr);

    printf("End sort: ");
    scanf_s("%d", &endstr);
    
    sort(array, n, startstr, endstr);

    printf("\nYour new matrix:\n\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("\t%d", array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
    return 0;
}

void sort(int** array, int rows, int startSort, int endSort)
{
    int sortlength = endSort - startSort;
    for (int i = 0; i < rows; i++)
    {
        for (int step = sortlength/2; step >0; step/=2)
        {
            for (int j = step; j < sortlength; j++)
            {
                for (int k = startSort + j - step; k >= 0 && array[i][k] > array[i][k + step]; k -= step)
                {
                    if (startSort != 0 && k == 0 || (k + step) >= endSort || k < startSort)
                        break;
                    int temp = array[i][k];
                    array[i][k] = array[i][k + step];
                    array[i][k + step] = temp;
                }
            }
        }
    }
}
