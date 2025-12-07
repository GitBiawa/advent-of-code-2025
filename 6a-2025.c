#include <stdio.h>
#include <errno.h> // for error handling
#include <string.h>
#include <stdlib.h>
#include <math.h>

// basically I decided it'd be funny to process everything while running
// not storing the big strings or anything like that
// also dealing with 4 file pointers at once, curious stuff

#define operandNumber 4

FILE * readFile(char * filename)
{
	FILE * filePtr = fopen(filename, "r");
	if (filePtr == NULL)
	{
		fprintf(stderr, 
	  		"%s: can't open %s: %s\n",
	  		"test.c", filename, strerror(errno));
	}
	return filePtr;
}

int setOperator(FILE * filePtr)
{
	int operator = 0;
	
	switch(fgetc(filePtr))
	{
	case 42:
		operator = 42;
		break;
	case 43:
		operator = 43;
		break;
	case 32:
		goto insideFunction;
	}
	
	long int position = 0;
	while(fgetc(filePtr) == 32) // 32 is whitespace
	{
		insideFunction:
		position = ftell(filePtr);
	}
	fseek(filePtr, position, SEEK_SET);

	return operator;
}

int getNumber(FILE * filePtr)
{
	// had to add in this block because I realized I
	// hadn't accounted for leading whitespace
	start:
	long int position = ftell(filePtr);
	if (fgetc(filePtr) != 32) {fseek(filePtr, position, SEEK_SET);}
	else {goto start;}

	int number = 0;
	char string[10] = {};
	int counter = 0;
	int temp = 0;
	// here we assume none of the numbers will exceed 10 digits
	// maybe a bit sussy, 10 is newline
	while (temp != 32 && temp != 10)
	{
		temp = fgetc(filePtr);
		string[counter] = temp;
		counter++;
	}
	
	// at position counter, there will be a space
	for (int i = 0; i < counter - 1; i++)
	{
		// decimal places are weird man
		number += (string[i] - '0') * pow(10, counter - i - 2);
	}

	if (temp == 32) {goto insideFunction;}
	while(fgetc(filePtr) == 32) // 32 is whitespace
	{
		insideFunction:
		position = ftell(filePtr);
	}
	fseek(filePtr, position, SEEK_SET);
	
	return number;
}

int pipeline(FILE ** pointerArray, long int * offsets)
{	
	int runningSum = 0;
	long int position = ftell(pointerArray[0]);
	// first line basically says, while we're in the line
	while (fgetc(pointerArray[0]) != '\n')
	{
		fseek(pointerArray[0], position, SEEK_SET);
		printf("%ld and %ld\n", ftell(pointerArray[0]), offsets[1] - 1);

		int operator = setOperator(pointerArray[operandNumber]);
		printf("%d as operator\n", operator);
		
		int currentNumber[operandNumber] = {0};
		for (int i = 0; i < operandNumber; i++)
		{
			currentNumber[i] = getNumber(pointerArray[i]);
		}
		position = ftell(pointerArray[0]);

		printf("current numbers are %d, %d, and %d\n", currentNumber[0], currentNumber[1], currentNumber[2]);
		
		// below could be switch statement?
		if (operator == 42) // 42 corresponds to *
		{
			int multiplication = 1;
			for (int i = 0; i < operandNumber; i++)
			{
				multiplication *= currentNumber [i];
			}
			runningSum += multiplication;
		}
		else if (operator == 43) // 43 corresponds to +
		{
			int addition = 0;
			for (int i = 0; i < operandNumber; i++)
			{
				addition += currentNumber[i];
			}
			runningSum += addition;
		}
	}
	return runningSum;
}

int main(void)
{
	int lineNumber = operandNumber + 1;
	
	FILE * filePtr = readFile("dat-6-2025");

	long int offsets[lineNumber] = {};
	offsets[0] = ftell(filePtr);

	int lineCounter = 0;
	while (lineCounter < lineNumber)
	{
		char character = fgetc(filePtr);
		if (character == '\n') 
		{
			offsets[lineCounter + 1] = ftell(filePtr);
			lineCounter++;
		}
	}
	fclose(filePtr); // we're done with seeking the line positions
	
	FILE * pointerArray[lineNumber];

	for (int i = 0; i < lineNumber; i++)
	{
		pointerArray[i] = readFile("dat-6-2025");
		fseek(pointerArray[i], offsets[i], SEEK_SET);
	}
	
	int result = pipeline(pointerArray, offsets);
	printf("%d\n", result);

	for (int i = 0; i < lineNumber; i++) {fclose(pointerArray[i]);}

	return 0;
}
