#include <stdio.h>
#include <stdlib.h>

/*int main()
{
	int a[2][2];
	int ** arr; // ** indicates 2 dimensions of memory for the array
	int i;
	arr = (int **)malloc(sizeof(int *)*2);
	for (i=0; i<2; i++)
	{
		arr[i] = (int *)malloc(sizeof(int)*2); // allocates space, but doesn't fill with data
	}

	// fill with data
	
	for (i=0; i<2; i++)
	{
		free(arr[i]); // frees the 2nd set of pointers
	}

	free(arr); // frees the 1st set of pointers 
}*/

int main()
{
	int a[3][3];
	int ** arr;
	int i, j, k;
	k = 1;
	arr = (int**)malloc(sizeof(int*) * 3);

	for (i=0; i<3; i++)
	{
		arr[i] = (int*)malloc(sizeof(int*) * 3); // allocates space for 3x3 array
	}

	// fill the array
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			arr[i][j] = k;
			printf("%d ", arr[i][j]);
			k++;
		}
		printf("\n");
	}

	// free memory
	for (i=0; i<3; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
