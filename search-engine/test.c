#include <hashmap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 20

int main(void)
{
	// Create map with user input
	int buckets = 0;
	printf("How many buckets do you want the hashmap to have? ");
	scanf("%d", &buckets);
	while (buckets < 1) {
		printf("Not a valid number, try again:\n");
		scanf("%d", &buckets);
	}
	struct hashmap* hm = hm_create(5);
		
	// "Train" the program by filling the hashmap
	add_file_contents(hm, "D1.txt");
	add_file_contents(hm, "D2.txt");
	add_file_contents(hm, "D3.txt");
	stop_word(hm);
	
	// Ask what the user wants to do
	char input = '\0';
	printf("Enter S to search or X to exit: ");
	scanf(" %c", &input);
	
	if (input == 88) {
		printf("Exiting...");
		hm_destroy(hm);
		return 0;
	}
	else if (input == 83) {
		// Let the user search until read_query returns -1 from #
		int ret = 1;
		while (ret > 0)
			ret = read_query(hm);
	}

	// Destroy the map
	hm_destroy(hm);

	return 0;
}
