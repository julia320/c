#include <stdio.h>

int main()
{
	int *arr = NULL;
	int i, j;
	int A[10];
	arr = (int *)malloc(sizeof (int)*20);
	for (i=0; i<20; i++)
	{
		arr[i] = i;
		printf("%dth index of arr is: %d\n", i, arr[i]);
	}
	free (arr); //frees excess memory 
	return 0;
}
