#include <stdio.h>
#include <string.h> // for strcspn
#include <errno.h> // for error handling
#include <stdlib.h>

long int absolute(long int number)
{
	if (number < 0){return (-number);}
	else{return number;}

}

int compareHalves(long int number)
{
	int array[15];
	int counter = 0;
	
	//long int intactNumber = number;
	while (number != 0)
	{
		array[counter] = number % 10;
		counter++;
		number = number / 10;
	}
	
	for (int i = 0; i < (counter / 2); i++)
	{	
		if (array[i] != array[counter / 2 + i])
		{
			return 0;
		}
		else if (i == counter / 2 - 1 && array[i] == array[counter / 2 + i])
		{
			//printf("%ld\n", intactNumber);
			return 1;
		}
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
	if ((numberOfDigits(number) % 2) == 0)
	{
		if (compareHalves(number) == 1)
		{
			testResult = 1;
		}
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
	char * filename = "dat-2-2025";
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
