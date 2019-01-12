#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	FILE *inputFile;
	char ch;

	inputFile = fopen(fileName, "r");
	ch = fgetc(inputFile);
	while (ch != EOF) {
		/* Process character ch */
		if (ch == ' ') {
			printf("\n");
		}
		else {
			printf(ch);
		}
	}
	fclose(inputFile);
}
