#include <stdio.h>
#include <errno.h> // for error handling
#include <string.h>
#include <stdlib.h>

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

// reads string line, converts @ to 1, . to 0
// then stores in multidim array
void stockLine(char * string, FILE * filePtr, int array[lineLength][numberOfRows + 2], int row)
{
	fgets(string, (lineLength + 2), filePtr);
	for (int j = 0; j < lineLength; j++)
	{
		if (string[j] == '.') {array[j][row] = 0;}
		else if (string[j] == '@') {array[j][row] = 1;}
	}
}

int letItRide(int array[lineLength][numberOfRows + 2])
{
	int rollCounter = 0;
	
	// don't ask me why these parameters work, I have no clue
	for (int row = 1; row < numberOfRows + 2; row++)
	{
		//print2DArray(array, numberOfRows, lineLength);

		
		for (int col = 0; col < lineLength; col++)
		{
			int firstColSum = 0;
			int lastColSum = 0;
			int surroundSum = 0;

			if (col == 0) {firstColSum = 0;}
			else
			{
      				firstColSum =
      				array[col - 1][row - 1] +
				array[col - 1][row] +
      				array[col - 1][row + 1];
			}

			if (col == lineLength - 1) {lastColSum = 0;}
			else 
			{
				lastColSum =
				array[col + 1][row - 1] +
				array[col + 1][row] +
				array[col + 1][row + 1];
			}

			surroundSum = 
			firstColSum +
			array[col][row - 1] +
			array[col][row + 1] +
			lastColSum;
			
			if (array[col][row] == 1 && surroundSum < 4)
			{
				array[col][row] = 0;
				rollCounter++;
			}
		}
	}
	return rollCounter;
}

int main(void)
{
	FILE * filePtr = readFile("dat-4-2025");

	// \0 appears twice ??
	char string[lineLength + 2];
	
	// we want 3 lines in memory at all times
	int lineArray[lineLength][numberOfRows + 2] = {0};
	
	// process all the rows intou our chonky array
	// by setting i to 1 we make the first row be full of zeroes, same for the end
	for (int i = 1; i < numberOfRows + 1; i++)
	{
		stockLine(string, filePtr, lineArray, i);
	}
	
	// loop our roll remover until it doesn't remove any
	int status = 1;
	int result = 0;
	while(status != 0)
	{
		status = letItRide(lineArray);
		result = result + status;
	}
	printf("\n%d can be removed\n\n", result);

	fclose(filePtr);
	return 0;
}
