#include <stdio.h>

int main()
{
	int a = 3;
	char *bytePtr = (char*)(&a); // points to the first byte of a
	int first = (int)*bytePtr;
	printf ("first byte of a is %d\n", first);
	int second = (int)*(bytePtr + 1);
	printf ("second byte of a is %d\n\n", second);

	int b = 127;
	char *byte = (char*)(&b); // points to first byte of b
	int firstB = (int)*byte;
	printf ("first byte of b is %d\n", firstB);
	int secondB = (int)*(byte + 1);
	printf ("second byte of b is %d\n", secondB);
	int thirdB = (int)*(byte + 2);
	printf ("third byte of b is %d\n", thirdB);
	int fourthB = (int)*(byte + 3);
	printf ("fourth byte of b is %d\n", fourthB);

	return 0;
}
