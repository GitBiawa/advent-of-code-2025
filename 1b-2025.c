// takes input filename and prints out all the contents, basically cat

#include <stdio.h>
#include <string.h> // for strcspn
#include <errno.h> // for error handling
#include <stdlib.h>

int main(void)
{
	char * filename = "dat-1-2025";
	FILE * filePtr = fopen(filename, "r");
	if (filePtr == NULL)
	{
		fprintf(stderr, 
	  		"%s: can't open %s: %s\n",
	  		"test.c", filename, strerror(errno));
    		return EXIT_FAILURE;
	}
	
	int wheelStatus = 50;
	int zeroCounter = 0;

	char ch[10];
	char *endptr;
	while ((fgets(ch, 10, filePtr)))
	{
		int num = strtol(ch, &endptr, 10);
		num = strtol(ch + 1, &endptr, 10);

		if (ch[0] == 'R')
		{
			while (num > 0)
			{
				wheelStatus = (wheelStatus + 1) % 100;
				if (wheelStatus == 0){zeroCounter++;}
				num--;
			}
		}
		else if (ch[0] == 'L')
		{ // weird stuff happening with negatives here
			while (num > 0)
			{
				int difference = (wheelStatus - 1) % 100;
				if (difference < 0){wheelStatus = 100 + difference;}
				else{wheelStatus = difference;}
				if (wheelStatus == 0){zeroCounter++;}
				num--;
			}
		}
	}

	printf("Zero was passed %d times. \n", zeroCounter);

	fclose(filePtr);
	return 0;
}
