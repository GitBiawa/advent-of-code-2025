#include <stdio.h>
#include <string.h> // for strcspn
#include <errno.h> // for error handling
#include <stdlib.h>
#include <math.h> // for pow

#define bankLength 100

typedef struct Tuple { // to be used in findMax
    int number;
    int position;
} Tuple;

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

void extractDigits(int * digitArray, int arraySize, char * string)
{
	for (int i = 0; i < arraySize; i++)
	{// extract digits
		digitArray[i] = string[i] - '0';
	}
}

Tuple findMax(int * digitArray, int arraySize)
{
	int maxNumber = 0;
	int maxPosition = 0;
	int counter = 0;

	while (counter < arraySize - 1)
	{
		if (digitArray[counter] > digitArray[counter + 1] && digitArray[counter] > maxNumber)
		{
			maxNumber = digitArray[counter];
			maxPosition = counter;
		}
		else if (digitArray[counter + 1] > maxNumber)
		{// equal case is not needed, as we prioritize the first find
			maxNumber = digitArray[counter + 1];
			maxPosition = counter + 1;
		}
		counter++;
	}
	
	Tuple max = {maxNumber, maxPosition};
	return max;
}

int main(void)
{
	FILE * filePtr = readFile("dat-3-2025");

	char string[bankLength + 2];
	// don't ask me why two more spaces, \n and ??
	long int totalJoltage = 0;

	while ((fgets(string, (bankLength + 2), filePtr)))
	{
		int digitArray[bankLength] = {0};
		extractDigits(digitArray, bankLength, string);
		
		// we chop off the last 11 digits at the start, since we're making 12 digit number
		int stopper = -1;
		long int maxJoltage = 0;
		for (int i = 11; i >= 0; i--)
		{
			int truncatedArray[bankLength - i];
			for (int j = 0; j < bankLength - i; j++)
			{
				if (j <= stopper){truncatedArray[j] = 0;}
				else {truncatedArray[j] = digitArray[j];}
			}
			Tuple max = findMax(truncatedArray, bankLength - i);
			stopper = max.position;
			
			maxJoltage = maxJoltage + (max.number * pow(10, i));
		}
		totalJoltage = totalJoltage + maxJoltage;
	}

	printf("%ld is the total Joltage\n", totalJoltage);

	fclose(filePtr);
	return 0;
}
