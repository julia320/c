#include <stdio.h>
#include <stdlib.h> // for malloc

/*int main()
{
	int * arr = NULL;
	int i, j;
	int a[10]; // array of size 10 -- easiest way to declare, but provides less data and clarification than malloc
	arr = (int *)malloc(sizeof(int)*25); // array of size 25 -- malloc allocates a certain amount of bytes of memory

	for (i=0; i<25; i++)
	{
		*(arr + i) = i; // same as arr[i] = i in Java; advances the memory location i spaces to reach the index
	}

	free(arr); // returns memory back to the system -- only need to use when malloc is called
}*/

int main() // odd #s descending from 25 to 1
{
	int * arr = NULL;
	int i, j;
	j = 1;
	arr = (int *)malloc(sizeof(int)*25);

	for (i=25; i>0; i--)
	{
		
		if (i%2)
		{
			*(arr + i) = i;
			if (j==1)
				printf("the %dst index of the array is %d\n", j, arr[i]);
			else if (j==2)
				printf("the %dnd index of the array is %d\n", j, arr[i]);
			else if (j==3)
				printf("the %drd index of the array is %d\n", j, arr[i]);
			else
				printf("the %dth index of the array is %d\n", j, arr[i]);
			j++;
		}
		
	}

	free(arr);
}
