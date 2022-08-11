#include <stdio.h>
#include <stdlib.h>


int main()
{
    int n = 0;
    int sum = 0;
    int pairs = 0;

    printf("Vvedite kolicestvo simvolov massiva  ");
    scanf("%d", &n);        

    int a[n];
    int b[n];
    for (int m = 0; m < n; m++)
    {
        a[m] = rand() % 15;
    }
    for (int m = 0; m < n; m++)
    {
        b[m] = rand() % 15;
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] * b[i] > 10)
        {
            pairs++;
            sum += a[i] * b[i];
            printf("a[%d]=%d b[%d]=%d ", i, a[i], i, b[i]);
        }
    }
    printf(" summa par=%d, kolicestvo par=%d", sum, pairs);
    return 0;
}