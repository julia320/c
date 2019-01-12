#include <stdio.h>

int main()
{
	char *first = "Julia";
	char *last = "Bristow";
	printf ("My first name is %c\n", *first);
	printf ("the 3rd letter of my name is %c\n", *(first+2));
		// this takes the memory location of the beginning of the string ("J") and moves over 2 spots ("l")
		// e.g. if "J" is at location 108, then "u" is at 109, "l" is at 110, and so on
	char ch = *(first + 5);
	if (ch == 0)
		printf("You have reached the end of your first name");
	else
		printf("You have not reached the end of your first name");
	return 0;
}
