#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

unsigned int query_index = 0;
double d1score = 0, d2score = 0, d3score = 0;

int read_query (struct hashmap* hm)
{
	// Reset the scores
	d1score = 0;
	d2score = 0;
	d3score = 0;

	// Retrieve the search query from the user
	char* query;
	printf("\nEnter a search query or hit \"#\" to exit: ");
	scanf(" %[^\n]s", query);

	// Check if they pressed #
	if ((int)query[0] == 35) {
		printf("Exiting...\n");
		return -1;
	}

	// Space to hold each word of the user input
	char* word = (char*)malloc(sizeof(char)*MAX_WORD_LENGTH);

	// Rank each word
	query_index = 0;
	while (query_index < strlen(query)) {
 		word = get_query_word(query, word);
		rank(hm, word);
	}

	// Show the results in order of score 
	//printf("SCORES - D1: %f, D2: %f, D3: %f\n", d1score, d2score, d3score);
	show_results();
	
	// Free the char array
	free(word);
	
	return 1;
}

void show_results ()
{
	printf("\nResults: ");
        if (d1score == 0 && d2score == 0 && d3score == 0)
                printf("No documents matched your search.\n");
	else if (d1score == d2score && d2score == d3score) 
		printf("All documents have the same rank\n\tD1.txt\n\tD2.txt\n\tD3.txt\n");
        else if (d1score > d2score && d1score > d3score) {
                printf("D1.txt\n");
                if (d2score > d3score) {
                        printf("\t D2.txt\n");
                        if (d3score > 0)
                                printf("\t D3.txt\n");
                }
                else if (d3score >= d2score && d3score > 0) {
                        printf("\t D3.txt\n");
                        if (d2score > 0)
                                printf("\t D2.txt\n");
                }
        }
        else if (d2score > d1score && d2score > d3score) {
                printf("D2.txt\n");
                if (d3score > d1score) {
                        printf("\t D3.txt\n");
                        if (d1score > 0)
                                printf("\t D1.txt\n");
                }
                else if (d1score >= d3score && d1score > 0) {
                        printf("\t D1.txt\n");
                        if (d3score > 0)
                                printf("\t D3.txt\n");
                }
        }
	else if (d3score > d1score && d3score > d2score) {
                printf("D3.txt\n");
                if (d2score > d1score) {
                        printf("\t D2.txt\n");
                        if (d1score > 0)
                                printf("\t D1.txt\n");
                }
                else if (d1score >= d2score && d1score > 0) {
                        printf("\t D1.txt\n");
                        if (d2score > 0)
                                printf("\t D2.txt\n");
                }
        }
        else
                printf("Problem with ranking\n");
}

char* get_query_word (char* query, char* word) 
{
	unsigned int i;
	int index = 0;

	// Clear the word array first
	for(i=0; i<MAX_WORD_LENGTH; i++) {
		word[i] = '\0';
	}

	// Separate a word and return it
	for (i=query_index; i<strlen(query); i++) {
		if (query[i] == ' ') {
			query_index = i+1;	
			break;
		}
		else {
			word[index] = query[i];
			index++;
			query_index++;
		}
	}
	return word;
}

void rank(struct hashmap* hm, char* word)
{
	// Get the node corresponding to the word
	struct llnode* node = hm_get(hm, word);
	
	// See if the word was actually in any of the documents
	if (node == NULL) {
		// If not, don't change the totals
		return;
	}
		
	// Add to the scores for each document
	d1score += tf_idf(node, "D1.txt");
	d2score += tf_idf(node, "D2.txt");
	d3score += tf_idf(node, "D3.txt");

	//printf("D1: %f, D2: %f, D3: %f\n", d1score, d2score, d3score);
}

double tf_idf (struct llnode* node, char* file_name)
{
	// Get the inverse document frequency
	double idf = get_idf(node);

	// Get the term frequency for the document
	double tf;
        if (strcmp(file_name, "D1.txt") == 0)
                tf = (double)node->d1_count;
        else if (strcmp(file_name, "D2.txt") == 0)
                tf = (double)node->d2_count;
        else
                tf = (double)node->d3_count;
	
        // Final score
        return tf*idf;
}

double get_idf (struct llnode* node)
{
        double df = 0;
        if (node->d1_count != 0) df++;
        if (node->d2_count != 0) df++;
        if (node->d3_count != 0) df++;
        return log(3/df);
}

