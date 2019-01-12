#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[])
{
	int i, total, avg;
	total = 0;

	if (strcmp(argv[1],"sum")==0) {
		for (i=1; i<argc; i++) {
			total = total+=atoi(argv[i+1]);
		}
		printf("the sum is %d", total);
	}

	else if (strcmp(argv[1],"difference")==0) {
		for (i=1; i<argc; i++) {
			total = total-=atoi(argv[i+1]);
		}
		printf("the difference is %d", total);
	}

	else if (strcmp(argv[1], "average")==0) {
		for (i=1; i<argc; i++) {
			total = total+=atoi(argv[i+1]);
		}
		avg = total/argc;
		printf("the average is %d", avg);
	}

	else {
		printf("Please enter \"sum\" \"difference\" or \"average\" followed by 1 or more numbers\n");
	}
}
