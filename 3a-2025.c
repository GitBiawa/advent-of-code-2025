#include <stdio.h>
#include <string.h> // for strcspn
#include <errno.h> // for error handling
#include <stdlib.h>

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
	int totalJoltage = 0;

	while ((fgets(string, (bankLength + 2), filePtr)))
	{
		int digitArray[bankLength] = {0};
		extractDigits(digitArray, bankLength, string);
		
		// we chop off the last digit, since we're making 2 digit number
		int truncatedArray[bankLength - 1] = {0};
		for (int i = 0; i < bankLength - 1; i++)
		{truncatedArray[i] = digitArray[i];}

		Tuple max1 = findMax(truncatedArray, bankLength - 1);

		int truncatedArray2[bankLength] = {0};
		for (int i = 0; i < bankLength; i++)
		{
       			if (i <= max1.position){truncatedArray2[i] = 0;}
       			else {truncatedArray2[i] = digitArray[i];}
       		}
		
		Tuple max2 = findMax(truncatedArray2, bankLength);
		
		int maxJoltage = max1.number * 10 + max2.number;
		totalJoltage = totalJoltage + maxJoltage;
	}

	printf("%d is the total Joltage\n", totalJoltage);

	fclose(filePtr);
	return 0;
}
