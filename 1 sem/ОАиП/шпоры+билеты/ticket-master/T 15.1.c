#include<stdio.h>
#include<math.h>
int perevod() 
{
	double x;
	int n1, k;
	printf("Enter x :");
	scanf_s("%lf", &x);
	printf("kol-vo sings after .");
	scanf_s("%d", &k);
	n1 = x;
	x = x - n1;
	x = x * pow(10, k);
	n1 = x + 1;
	printf("%d\n", n1);
	return n1;
}
void function(int x, int n)
{
	if (x == 0 || x < n)
	{
		if ((n < 10) || (x < 10)) printf("%d", x);
		else
			switch (x)
			{
			case 10: printf("A");
				break;
			case 11: printf("B");
				break;
			case 12: printf("C");
				break;
			case 13: printf("D");
				break;
			case 14: printf("E");
				break;
			case 15: printf("F");
				break;
			case 16: printf("G");
				break;
			}
	}
	else
	{
		int ostatok = x % n;
		x = x / n;
		function(x, n);
		if ((n < 10) || (ostatok < 10)) printf("%d", ostatok);
		else
			switch (ostatok)
			{
				case 10: printf("A");
					break;
				case 11: printf("B");
					break;
				case 12: printf("C");
					break;
				case 13: printf("D");
					break;
				case 14: printf("E");
					break;
				case 15: printf("F");
					break;
				case 16: printf("G");
					break;
			}
	}
}
 
int main ()
{
	int n;
	printf("Enter n : ");
	scanf_s("%d", &n);
	function(perevod(), n);
	return 0;
}
 
