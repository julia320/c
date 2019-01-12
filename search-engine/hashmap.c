#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

struct hashmap* hm_create(int num_buckets)
{
	int i;

	// Allocate space for hash map
	struct hashmap* hm = (struct hashmap*)malloc(sizeof(struct hashmap));
	// Fill fields of hash map
	hm->map = (struct llnode**)malloc(sizeof(struct llnode*)*num_buckets);
	hm->num_buckets = num_buckets;
	hm->num_elements = 0;

	// Allocate space for the head of each list
	for (i=0; i<num_buckets; i++) {
		hm->map[i] = (struct llnode*)malloc(sizeof(struct llnode));
 	        // Initialize everything in the head
        	hm->map[i]->word = NULL;
        	hm->map[i]->d1_count = 0;
		hm->map[i]->d2_count = 0;
		hm->map[i]->d3_count = 0;
        	hm->map[i]->next = NULL;
	}

	return hm;
}

struct llnode* hm_get(struct hashmap* hm, char* word)
{
	// Get the equivalent hash
	int h = hash(hm, word);
	// Iterator starting at the head
    	struct llnode* curr_node = hm->map[h];

    	// Iterate through the nodes with this hash
    	while(curr_node->word != NULL) {
        	// See if the word is there
        	if (strcmp(curr_node->word, word)==0) {
            		return curr_node;
        	}
        	// If not there, keep going
        	curr_node = curr_node->next;
    	}

    	// If we get here, then the combination never occurred
	return NULL;
}

void hm_put(struct hashmap* hm, char* word, int d1_count, int d2_count, int d3_count)
{
	// Get the corresponding hash
	int h = hash(hm, word);

    	// Get the node containing the word (will return NULL if none)
    	struct llnode* node = hm_get(hm, word);

	// If the word doesn't exist yet, create it
	if (node == NULL) {
		struct llnode* new_node = (struct llnode*)malloc(sizeof(struct llnode));
    		new_node->word = word;
    		new_node->d1_count = d1_count;
		new_node->d2_count = d2_count;
		new_node->d3_count = d3_count;
    		
    		// Set pointers so that the head gets replaced
    		new_node->next = hm->map[h];
    		hm->map[h] = new_node;

    		// Increment num elements in the hashmap
    		hm->num_elements++;
	}
	// Otherwise, we just need to update the values in the node we got
	else {
		node->d1_count = d1_count;
		node->d2_count = d2_count;
		node->d3_count = d3_count;
	}
}

void hm_remove(struct hashmap* hm, char* word)
{
	// Get the equivalent hash
	int h = hash(hm, word);

	// Empty check
	if (hm->map[h]->word == NULL) {
		return;
	}

	// Iterator starting at the head
	struct llnode* curr_node = hm->map[h];
    	struct llnode* prev = curr_node;

    	// Iterate through the nodes with this hash
    	while(curr_node->word != NULL) {
        	// See if the word is there
        	if (strcmp(curr_node->word, word)==0) {

        		// If removing the head (will happen on the first run if true)
		    	if (prev == curr_node) {
				curr_node = hm->map[h];
		    		hm->map[h] = hm->map[h]->next;
		    	}
		    	else { // Re-assign pointer, not the head
		    		prev->next = curr_node->next;
		    	}

			free(curr_node);
        		hm->num_elements--;
        		return;
        	}

        	// If not there, keep going
        	prev = curr_node;
        	curr_node = curr_node->next;
    	}
}

void hm_destroy(struct hashmap* hm)
{	
	int i;
	struct llnode* temp;

	// Free all the necessary nodes in each list
	for (i=0; i<hm->num_buckets; i++) {
		struct llnode* curr_node = hm->map[i];
		// Go through the list until there are no more nodes
		while (curr_node != NULL) {
			// Free the current node
			temp = curr_node;
			free(curr_node);
			curr_node = temp->next;
		}
	}
	// Free the pointers to the whole thing
	free(hm->map);
	free(hm);
}

int hash(struct hashmap* hm, char* word)
{
	unsigned int i = 0;
	int asciiTotal = 0;//, length = strlen(word);
	int hash;

	// Add the ascii values of each char to the total
	for (i=0; i<strlen(word); i++) {
		asciiTotal += (int)word[i];
	}

	// Modulo with the number of buckets to get a num in that range
	hash = asciiTotal % hm->num_buckets;

	return hash;
}
