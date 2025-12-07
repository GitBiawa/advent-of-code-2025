#include <stdio.h>
#include <errno.h> // for error handling
#include <string.h>
#include <stdlib.h>

#define lineLength 16
#define rowNumber 15

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

int switcheroo(int character, int beams[lineLength], int index)
{
	int splits = 0;

	switch (character)
	{
		case 46: // 46 is empty space
			break;
		case 94: // 94 is splitter
			splits++; // we have split a beam
			beams[index] = 0; // there will be no beam going past the splitter
			if (index > 0 && index < lineLength - 1)
			{
				beams[index - 1] = 1;
				beams[index + 1] = 1;
			}
			else if (index == 0) {beams[index + 1] = 1;}
			else if (index == lineLength - 1) {beams[index - 1] = 1;}
		case 83: // 83 is S
			beams[index] = 1;
	}
	return splits;
}

int runManifold(FILE * filePtr, int beams[lineLength])
{
	int totalSplits = 0;
	for (int i = 2; i < rowNumber; i = i + 2)
	{
		char string[lineLength + 2] = {};
		// calling fgets twice and advancing by 2 because every 2nd row is empty
		fgets(string, lineLength + 2, filePtr);
		fgets(string, lineLength + 2, filePtr);

		int tempBeams[lineLength] = {0};
		for (int j = 0; j < lineLength; j++)
		{
			if (beams[j] == 1) 
			{
       				totalSplits += switcheroo(string[j], tempBeams, j);
				printf("total splits at %d in row %d\n", totalSplits, i);
			}
		}

		for (int k = 0; k < lineLength; k++)
		{
			beams[k] = tempBeams[k];
			if (beams[k] == 0) {printf(".");}
			if (beams[k] == 1) {printf("|");}
		}
		puts("");
	}
	return totalSplits;
}

int main(void)
{
	FILE * filePtr = readFile("dat-test");
	
	// + 2 for \0\0
	char string[lineLength + 2] = {};
	fgets(string, lineLength + 2, filePtr);
	
	// 0 marks no beams, 1 marks a beam
	int beams[lineLength] = {0};

	// we determine where the S is
	for (int i = 0; i < lineLength; i++)
	{
		switcheroo(string[i], beams, i);
	}

	int result = runManifold(filePtr, beams);
	printf("result is %d\n", result);

	fclose(filePtr);

	return 0;
}
