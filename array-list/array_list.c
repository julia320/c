#include "array_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INITIAL_SIZE 10

/* Question 2: An array list has a faster access time because you just 
	have to tell it which index to look at (O(1)), whereas with a linked 
	list you have to iterate through the list to find something (O(n)).

	An array list has an add time of O(1) because you just need to add 
	to the next index, but if you need to resize it because you went over
	capacity then it would be O(n). A linked list has a rear pointer so 
	that would also be O(1) since you just need to re-arrange the pointers 
	and you already know where it is.

	The remove time for an array list is O(n) because you have to shift 
	everything to the left and in the worst case this would be n elements.
	A linked list is also O(n) if you remove something in the middle 
	because you have to iterate through to find where you need to start 
	changing pointers, but if you are removing from the end it would be 
	O(1) for the same reason as the add function.
*/

// return type		name	parameters
struct array_list* al_create (void)
{
	//struct array_list;
	struct array_list* list;
	list = malloc(sizeof(struct array_list));
	list->size = 0;
	list->capacity = INITIAL_SIZE;
	list->array = (int*)malloc(sizeof(list->capacity));
	return list;
}

void al_add (struct array_list* list, int value)
{
	// cHeCk tO MaKe sURe tHe LiSt eXiStS
	if (list == NULL) {
		printf("Error: List has not been initialized");
		return;
	}

	//int i;

	// if not going past the max capacity
	if (list->size < list->capacity)
		list->array[list->size] = value;

	// otherwise we need to add space
	else {
		printf("re-allocating space\n");
		list->capacity = list->capacity * 1.5;
		printf("new list capacity: %d\n", list->capacity);
		// re-allocate the array - have to store it somewhere first
		int* temp = (int*)malloc(sizeof(list->capacity));
		temp = (int*)realloc(list->array,sizeof(list->capacity));
		list->array = temp;
		free(temp);
		
		// now add the value to the array
		list->array[list->size] = value;
	}
	// increment the size 
	list->size++;
}

int al_get (struct array_list* list, int index)
{
	// cHeCk tO MaKe sURe tHe LiSt eXiStS
	if (list == NULL) {
		printf("Error: List has not been initialized");
		return 0;
	}
	printf("Element at %d is %d\n", index, list->array[index]);
	return list->array[index];
}

void al_set(struct array_list* list, int index, int value)
{
	// cHeCk tO MaKe sURe tHe LiSt eXiStS
	if (list == NULL) {
		printf("Error: List has not been initialized");
		return;
	}
	printf("Setting %dth element to %d\n",index,list->array[index]);
	list->array[index] = value;
}

void al_remove(struct array_list* list, int index)
{
	// cHeCk tO MaKe sURe tHe LiSt eXiStS
	if (list == NULL) {
		printf("Error: List has not been initialized");
		return;
	}

	// shift everything to the left 1 from index to size-1
	int i;
	for (i=index; i<list->size-1; i++) {
		list->array[i] = list->array[i+1];
	}
	// nothing should be at the last spot anymore
	list->array[(list->size)-1] = -1;
}

int al_size(struct array_list* list)
{
	// cHeCk tO MaKe sURe tHe LiSt eXiStS
	if (list == NULL) {
		printf("Error: List has not been initialized");
		return 0;
	}

	return list->size;
}

void al_destroy(struct array_list* list)
{
	free(list->array);
	free(list);
}