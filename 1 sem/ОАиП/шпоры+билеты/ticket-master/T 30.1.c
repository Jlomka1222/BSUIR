#include <stdio.h>
#include <stdlib.h>

int main() {
    int k = 0, b = 0, j = 0;
    int pos1 = 0, pos2 = 0;
    int n;
    float temp = 0.0;
    double* result;
    double* firstArray;
    double* secondArray;
    printf("Enter a number of elements in the first array: \n");
    scanf_s("%d", &n);
    firstArray = (double*)calloc(n, sizeof(double));
    printf("Enter elements: \n");
    for (int i = 0; i < n; i++) {
        printf("[%d] ", i + 1);
        scanf_s("%lf", &firstArray[i]);
        while (temp < firstArray[i] && (i != 0)) {
            printf("Enter again: \n");
            printf("[%d] ", i + 1);
            scanf_s("%lf", &firstArray[i]);
        }
        temp = firstArray[i];
    }

    temp = 0.0;

    printf("Enter a number of elements in the second array: \n");
    secondArray = (double*)calloc(n, sizeof(double));
    printf("Enter elements: \n");
    for (int i = 0; i < n; i++)
    {
        printf("[%d] ", i + 1);
        scanf_s("%lf", &secondArray[i]);
        while (temp < secondArray[i] && (i != 0))
        {
            printf("Enter again: \n");
            printf("[%d] ", i + 1);
            scanf_s("%lf", &secondArray[i]);
        }
        temp = secondArray[i];
    }

    for (int i = 0; i < n; i++)
    {
        printf("%5.2lf  ", firstArray[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%5.2lf  ", secondArray[i]);
    }
    printf("\n");

    b = n - 1, j = n - 1;

    result = (double*)calloc(2 * n, sizeof(double));
    while (k < 2 * n)
    {
        while (b >= 0)
        {
            while (j >= 0)
            {

                if (firstArray[j] < secondArray[b])
                {
                    result[k] = firstArray[j];
                    k++;
                    j--;
                }
                else
                {
                    result[k] = secondArray[b];
                    k++;
                    b--;

                }
//                if (b == 0 && j== 0)
//                {
//                    k++;
//                    result[k] = firstArray[j];
//                }
            }
            result[k] = secondArray[b];
            k++;
            b--;

        }
    }
    for (int i = 0; i < 2 * n; i++)
    {
        printf("%10.2lf", result[i]);
    }
    free(result);
    free(firstArray);
    free(secondArray);
    return 0;

}
