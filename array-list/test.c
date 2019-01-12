#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"

int main(void)
{
	// test adding
	struct array_list* list = al_create();
	int i;
	for(i=0; i<20; i++) {
		al_add(list, i);
	}

	// test removing
	al_remove(list, 6);
	printf("removing 6th index:\n");

	al_remove(list, 12);
	printf("removing 12th index:\n");

	// test get
	al_get(list, 3);

	// test set
	al_set(list, 15, 100);

	// test size
	printf("There are %d elements in the list", al_size(list));

	// destroy the list
	al_destroy(list);
	return 0;
}
