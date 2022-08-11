#include <stdio.h>
//#include <malloc.h>
//void TransposeMatrix(int** matrix, int size);
//int main()
//{
//    int n;
//    int** matrix;
//    printf("Enter a size of matrix: \n");
//    scanf_s("%d", &n);
//    printf("Enter a values: \n");
//    matrix = (int**)calloc(n, sizeof(int*));
//    for (int i = 0; i < n; i++)
//    {
//        matrix[i] = (int*)calloc(n, sizeof(int));
//        for (int j = 0; j < n; j++)
//        {
//            scanf_s("%d", &matrix[i][j]);
//        }
//    }
//
//    for (int i = 0; i < n; i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            printf("%5d", matrix[i][j]);
//        }
//        printf("\n");
//    }
//
//    printf("\n");
//
//    TransposeMatrix (matrix, n);
//
//
//    for (int i = 0; i < n; i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            printf("%5d", matrix[i][j]);
//        }
//        printf("\n");
//    }
//
//
//    return 0;
//}
//
//void TransposeMatrix(int** matrix, int size)
//{
//    int temp = 0;
//    static int i = 0;
//    static int j = 0;
//
//    temp = matrix[i][j];
//    matrix[i][j] = matrix[size - 1 - j][size - 1 - i];
//    matrix[size - 1 - j][size - 1 - i] = temp;
//
//    if (j < size - 1 - i)
//    {
//        ++j;
//        TransposeMatrix(matrix, size);
//    }
//
//    if (i < size - 1)
//    {
//        ++i;
//        j = 0;
//        TransposeMatrix(matrix, size);
//    }
//
//    return;
//}
//


#include <stdio.h>
#include <malloc.h>
void DeleteWord(char* string, int length, int position, int lengthOfString);
int main()
{
	int n; 
	int length = 0, position = 0, lengthOfLastWord = 0, counter = 0;
	char* string;

	printf("Enter a number of elements in string: \n");
	scanf_s("%d", &n);

	printf("Enter a string: \n");
	string = (char*)calloc(n + 1, sizeof(char));
	rewind(stdin);
	fgets(string, n + 1, stdin);

	for (int i = n; i >= 0; i--)
	{
		while (string[i] != ' ')
		{
			i--;
			lengthOfLastWord++;
			if (string[i] == ' ')
			{
				counter++;
			}
		}
		if (counter == 1)
		{
			i--;
			while (string[i] != ' ')
			{
				position = i;
				length++;
				i--;
			}
		}
	}

 	DeleteWord(string, length, position, n);

	puts(string);

	free(string);

	return 0;
}
void DeleteWord(char* string, int length, int position, int lengthOfString)
{
	string[position] = string[position + length + 1];
	if (position < lengthOfString)
	{
		position++;
		DeleteWord(string, length, position, lengthOfString);
	}
	
}
