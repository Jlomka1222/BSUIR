#include <stdio.h>
#include <stdlib.h>
void DeleteWord(int argc, char* argv);
int main(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		printf("\nprevious string: %s", argv[i]);
		DeleteWord(argc, argv[1]);
		printf("\nnew string: %s", argv[i]);
	}


	return 0;
}

void DeleteWord(int argc, char* argv)
{
	char* temp;
	temp = (char*)calloc(1, sizeof(char));
	int length = 0, end = 0, count = 0, i = 0, word = 0, j = 0, start = 0;
	while (argv[length] != '\0')
	{
		length++;
	}
	while (argv[i] != ' ')
	{
		i++;
		if (argv[i] == ' ')
		{
			count++;
		}
		if (count == 1)
		{
			break;
		}
	}
	end = i;
	temp = (char*)realloc(temp, end + 1);
	for (int j = 0; j < end; j++)
	{
		temp[j] = argv[j];
	}
	temp[end] = '\0';
	/*printf("\n");
	puts(temp);*/
	//delete first word

	for (int i = 0; i < length + 1; i++)
	{
		argv[i] = argv[i + end + 1];
	}

	i = 0;
	j = 0;
	while (argv[i] != '\0' && temp[j])
	{
		if (argv[i] == temp[j])
		{
			start = i;
			while (argv[i] == temp[j] && j < end)
			{
				i++;
				j++;
			}
			if (j == end)
			{
				end = i;
				int len = end - start;
				for (int k = start; k < length + 1; k++)
				{
					argv[k] = argv[k + len + 1];
				}
				j = 0;
			}

		}
		i++;
	}
}

