#include <stdio.h>

int main()
{
	int i;
	i=3;
	if (i==1) {
		for (i=1; i<16; i++) {
			if (i%2 == 1)
				printf("odd number %d\n", i);
		}
	}
	else if (i==2) {
		for (i=1; i<16; i++) {
			if (i%2 == 0)
				printf("even number %d\n", i);
		}
	}
	else {
		for (i=1; i<16; i++) {
			printf("number %d\n", i);
		}
	}
}
