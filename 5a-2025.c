#include <stdio.h>
#include <errno.h> // for error handling
#include <string.h>
#include <stdlib.h>

#define lineLength 31
#define numberOfRanges 183

FILE * readFile(char * filename)
{
	FILE * filePtr = fopen(filename, "r");
	if (filePtr == NULL)
	{
		fprintf(stderr, 
	  		"%s: can't open %s: %s\n",
	  		"test.c", filename, strerror(errno));
    		//return EXIT_FAILURE;
	}
	return filePtr;
}

void cacheFreshFoods(long int array[numberOfRanges][2], FILE * filePtr)
{
	char string[lineLength + 2];
	
	for (int i = 0; i < numberOfRanges; i++)
	{
		fgets(string, (lineLength + 2), filePtr);
		char * endptr;
		array[i][0] = strtol(string, &endptr, 10);
		array[i][1] = -strtol(endptr, &endptr, 10);
	}

	// this eats the empty line
	fgets(string, (lineLength + 2), filePtr);
}

int evaluateItem(long int array[numberOfRanges][2], FILE * filePtr)
{
	int freshCounter = 0;
	char string[lineLength + 2];
	
	while(fgets(string, (lineLength + 2), filePtr) != NULL)
	{
		char * endptr;
		long int number = strtol(string, &endptr, 10);
		
		for (int i = 0; i < numberOfRanges; i++)
		{
			if (number >= array[i][0] && number <= array[i][1])
			{
				freshCounter++;
				break;
			}
		}
	}
	return freshCounter;
}

int main(void)
{
	FILE * filePtr = readFile("dat-5-2025");
	
	long int freshFood[numberOfRanges][2] = {0};
	cacheFreshFoods(freshFood, filePtr);
	
	int result = evaluateItem(freshFood, filePtr);
	printf("There are %d fresh items.\n", result);

	fclose(filePtr);

	return 0;
}
