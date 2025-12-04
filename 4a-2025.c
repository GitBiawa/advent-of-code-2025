#include <stdio.h>
#include <errno.h> // for error handling
#include <string.h>
#include <stdlib.h>
#include <math.h> // for pow

#define lineLength 139
#define numberOfRows 139

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

// array printing, for debugging purposes
// for some reason it only works if those 3s are in there
void print2DArray(int array[3][3], int sizeA, int sizeB)
{
	for (int i = 0; i < sizeA; i++)
	{
		for (int j = 0; j < sizeB; j++)
		{
			printf("%d", array[j][i]);
		}
		puts("");
	}
}

// reads string line, converts @ to 1, . to 0
// then stores in multidim array
void stockLine(char * string, FILE * filePtr, int array[3][3], int row)
{
	fgets(string, (lineLength + 2), filePtr);
	for (int j = 0; j < lineLength; j++)
	{
		if (string[j] == '.') {array[j][row] = 0;}
		else if (string[j] == '@') {array[j][row] = 1;}
	}
}

void moveDown(char * string, FILE * filePtr, int array[3][3], int row)
{
	for (int i = 0; i < lineLength; i++)
	{
		array[i][0] = array[i][1];
		array[i][1] = array[i][2];
	}

	if (row < numberOfRows - 1)
	{
		stockLine(string, filePtr, array, 2);
	}
	else
	{ // setting to zero because it would be out of bounds
		for (int j = 0; j < lineLength; j++) {array[j][2] = 0;}
	}
}

int letItRide(char * string, FILE * filePtr, int array[3][3])
{
	int rollCounter = 0;
	
	// don't ask me why these parameters work, I have no clue
	for (int row = 1; row < numberOfRows + 2; row++)
	{
		
		for (int col = 0; col < lineLength; col++)
		{
			int firstColSum = 0;
			int lastColSum = 0;
			int surroundSum = 0;

			if (col == 0) {firstColSum = 0;}
			else
			{
      				firstColSum =
      				array[col - 1][0] +
				array[col - 1][1] +
      				array[col - 1][2];
			}

			if (col == lineLength - 1) {lastColSum = 0;}
			else 
			{
				lastColSum =
				array[col + 1][0] +
				array[col + 1][1] +
				array[col + 1][2];
			}

			surroundSum = 
			firstColSum +
			array[col][0] +
			array[col][2] +
			lastColSum;
			
			if (array[col][1] == 1 && surroundSum < 4)
			{
				rollCounter++;
			}
		}
		moveDown(string, filePtr, array, row);
	}
	return rollCounter;
}

int main(void)
{
	FILE * filePtr = readFile("dat-4-2025");

	// \0 appears twice ??
	char string[lineLength + 2];
	
	// we want 3 lines in memory at all times
	int lineArray[lineLength][3] = {0};
	
	// process the first three lines, the rest will be done in a loop
	// by setting i to 1 we make the first row be full of 0 
	for (int i = 1; i < 3; i++)
	{
		stockLine(string, filePtr, lineArray, i);
	}
	
	int test = letItRide(string, filePtr, lineArray);
	printf("\n%d can be accessed\n\n", test);

	fclose(filePtr);
	return 0;
}
