#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_WORD_LENGTH 20

bool file_cmplt = false;

void train (struct hashmap* hm, char* file1, char* file2, char* file3)
{
	// Add the words from the files
	add_file_contents(hm, file1);
	printf("added 1\n");
	add_file_contents(hm, file2);
	printf("added 2\n");
	add_file_contents(hm, file3);
	printf("added 3\n");

	// Remove all stop words
	stop_word(hm);
	printf("stop words\n");
}

void add_file_contents (struct hashmap* hm, char* input_file_name)
{
        // Open the file
        FILE* in;
        in = fopen(input_file_name, "r");
        
        file_cmplt = false;
        
	// Check that the file exists
        if (in == NULL) {
        	printf("Error opening the file");
                return;
        }
        
        // While there are still words left in the file
        while (!file_cmplt) {
        	// Retrieve a word
                char* word = get_next_word(in);
                                                                                                                  // Check whether the word is already in the hashmap
                struct llnode* node = hm_get(hm, word);
                if (node == NULL) {
        		// Put it with the right value depending on which file it is
                        if (strcmp(input_file_name, "D1.txt") == 0)
        	                hm_put(hm, word, 1, 0, 0);
                        else if (strcmp(input_file_name, "D2.txt") == 0)
                                hm_put(hm, word, 0, 1, 0);
                        else
                                hm_put(hm, word, 0, 0, 1);
        	}
                // If it was already there, we just need to increment the value
                else {
       	        	if (strcmp(input_file_name, "D1.txt") == 0)
        	        	hm_put(hm, word, node->d1_count+1, node->d2_count, node->d3_count);
			else if (strcmp(input_file_name, "D2.txt") == 0)
				hm_put(hm, word, node->d1_count, node->d2_count+1, node->d3_count);
			else
				hm_put(hm, word, node->d1_count, node->d2_count, node->d3_count+1);
                }
        }
        
	// Close the file
        fclose(in);
}

char* get_next_word (FILE* in)
{
        char* word = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);
        int index = 0;

        // Get the char from current location
        char ch = fgetc(in);   

	// Iterate through until we reach a space
	while (ch != EOF) {
                if (ch == ' ' || ch == '\n') return word;

                // Add char to the word if it wasn't a space
                else {
                	word[index] = ch;
                        index++;
                }
                
		// Get the next char
                ch = fgetc(in);
	}

        // If the file ended, we still want to return the word
        file_cmplt = true;
        return word;
}

void stop_word (struct hashmap* hm)
{
	int i;

	// Iterate through all the nodes
	for (i=0; i<hm->num_buckets; i++) {
                struct llnode* curr_node = hm->map[i];
		while(curr_node->word != NULL) {
			// Get the tf_idf value and see if it should be a stop word
			double idf = get_idf(curr_node); 
			if (idf == 0)
				hm_remove(hm, curr_node->word);                      
                        curr_node = curr_node->next;
                }
	}	
}

void print (struct hashmap* hm)
{
        printf("\nPrinting the hashmap...");
        int i, x;

        for (i=0; i<hm->num_buckets; i++) {
                printf("\nBucket %d\n", i);

                // Iterator
                struct llnode* curr_node = hm->map[i];
                x = 1;

                while(curr_node->word != NULL) {
                        printf("\tNode %d: ", x);
                        printf("Word: %s\n", curr_node->word);
                        printf("\t\tDoc D1 count: %d\n\t\tDoc D2 count: %d\n\t\tDoc D3 count: %d\n",
                             curr_node->d1_count, curr_node->d2_count, curr_node->d3_count);
                        x++;
                        curr_node = curr_node->next;
                }
        }
}

