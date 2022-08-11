#include <stdarg.h>
#include <stdio.h>
enum data {Int, Float = 2} type;
void SumOfIntegersAndFloats(int numberOfGroups, int numberOfElements, enum data type, ...);
int main()
{
	SumOfIntegersAndFloats(3, 2, Int, 1, 2, 2, Float, 1.2, .8, 4, Int, 2, 3, 4, 5);
	printf("\n");
	return 0;
}

void SumOfIntegersAndFloats(int numberOfGroups, int numberOfElements, enum data type, ...)
{
	int sumOfIntegers = 0;
	float sumOfFloats = 0;

	va_list pointer;
	va_start(pointer, type);
	while (numberOfGroups--)
	{
		switch (type)
		{
		case Int: while (numberOfElements--)
			sumOfIntegers += va_arg(pointer, int);
			break;
		case Float: while (numberOfElements--)
			sumOfFloats += va_arg(pointer, double);
			break;
		}
		numberOfElements = va_arg(pointer, int);
		type = va_arg(pointer, enum data);
		
	}
	va_end(pointer);
	printf("Sum of Integers: %d, sum of floats: %lf\n", sumOfIntegers, sumOfFloats);
}
