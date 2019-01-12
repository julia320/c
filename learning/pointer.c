#include <stdio.h>

int main ()
{
	int i = 3;
	int *p;
	printf("the value of i is %d\n", i);
	p = &i;
	printf("the value of i is %d and is at memory address %p\n", i, p);
	*p = *p + 1;
	printf("the value of i is %d and is at memory address %p\n", i, p);
}


