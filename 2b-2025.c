#include <stdio.h>
#include <string.h> // for strcspn
#include <errno.h> // for error handling
#include <stdlib.h>

long int absolute(long int number)
{
	if (number < 0){return (-number);}
	else{return number;}

}

int findRepetitions(long int number)
{ // shoulda separated this into mor functions, but I'm eepy
	int array[15];
	int counter = 0;
	
	long int intactNumber = number;
	while (number != 0)
	{
		// the array will be the number mirrored, but this is irrelevant
		array[counter] = number % 10;
		counter++;
		number = number / 10;
	}
	
	int divisor = counter;
	int similarityScore = 0;

	while (divisor > 1) // we don't want the case 1
	{
		// filter out the integer separations that can be made, based on digits
		if (counter % divisor == 0)
		{// this loop runs each valid divisor of digits
			int spacingUnit = counter / divisor;

			for (int i = 0; i < divisor - 1; i++)
			{// this loop runs each required comparison, independent of spacing
				for (int j = 0; j < spacingUnit; j++)
				{// this loop compares each digit
					if (array[j] != array[j + spacingUnit])
	 				{return 0;}

	 				else if (array[j] == array[j + spacingUnit])
					{// we keep track of previous matches
	 				// similarityScore should be divisor - 1 for full matches
					// this shouldn't be necessary due to the previous if statement??? 
	 					similarityScore++;
	 					if(i == divisor - 2 && similarityScore == divisor - 1) 
	       					{printf("%ld is sus, with spacing unit %d, and divisor %d\n", intactNumber, spacingUnit, divisor);}
	 				}
				}
			}
		}
		divisor--;
	}
	
	return 0;
}

int numberOfDigits(long int number)
{
	int counter = 0;
	
	while (number != 0)
	{
		counter++;
		number = number / 10;
	}
	return counter;
}

int testValidity(long int number)
{ // returns 1 if the ID is invalid
	int testResult = 0;
	if (findRepetitions(number) == 1)
	{
		testResult = 1;
	}
	
	return testResult;
}

long int processRange(char * string)
{
	long int repetitions = 0;
	
	char *endptr;
	long int numA = strtol(string, &endptr, 10);
	
	// hyphen is taken as negative, so we do abs
	long int numB = absolute(strtol(endptr, &endptr, 10));
	long int range = numB - numA;
	
	//printf("from %ld to %ld, the range is %ld\n", numA, numB, range);
	while (range >= 0)
	{
		if (testValidity(numA))
		{
			repetitions = repetitions + numA;
		}

		numA++;
		range--;
	}
	return repetitions;
}

int main(void)
{
	char * filename = "dat-test";
	FILE * filePtr = fopen(filename, "r");
	if (filePtr == NULL)
	{
		fprintf(stderr, 
	  		"%s: can't open %s: %s\n",
	  		"test.c", filename, strerror(errno));
    		return EXIT_FAILURE;
	}
	
	// string for each range
	char string[50];
	int stringCounter = 0;
	
	// storage for current character
	int currentChar = 0;

	// storage for final answer
	long int bigSum = 0;

	while (currentChar != EOF)
	{
		currentChar = fgetc(filePtr);
		// OR EOF because there's no trailing comma
		if (currentChar == ',' || currentChar == EOF)
		{
			long int repetitions = processRange(string);
			bigSum = bigSum + repetitions;

			// need to reset the string
			stringCounter = 0;
			for (int i = 0; i < 50; ++i) 
			{
    				string[i] = ' ';
			}
		}
		else
		{
			// adding the character to the string
			string[stringCounter] = currentChar;	
		}
		stringCounter++;
	}
	printf("sum is %ld\n", bigSum);
	fclose(filePtr);
	return 0;
}
