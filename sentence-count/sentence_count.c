#include "sentence_count.h"
#include <stdio.h>

/* Question 1: this code runs in O(n) if n is the number of chars
	in the file because it goes through each char to check what it is */

void sentence_count(char* input_file_name, char* output_file_name) 
{
	// open the file
	FILE* in;
	in = fopen(input_file_name, "r");

	// get the first char
	char ch;
	ch = fgetc(in);

	// keep track of the number of sentences, exclamations, and questions
	int sentCount = 0;
	int exclCount = 0;
	int quesCount = 0;
	int total = 0;

	// check that the file exists
	if (in == NULL) {
		printf("Error opening the file");
		return;
	}

	// while not End Of File, check for punctuation
	while (ch != EOF) {

		// "." indicates a sentence
		if (ch == '.') {
			sentCount++;
			total++;
		}
		// "!" indicates an exclamation
		else if (ch == '!') {
			exclCount++;
			total++;
		}
		// "?" indicates a question
		else if (ch == '?') {
			quesCount++;
			total++;
		}

		// get the next char
		ch = fgetc(in);
	}

	// close the file
	fclose(in);

	// output the results to a new file
	FILE* out = fopen(output_file_name, "w");
	fprintf(out, "Statement Count: %d\n", sentCount);
	fprintf(out, "Exclamation Count: %d\n", exclCount);
	fprintf(out, "Question Count: %d\n", quesCount);
	fprintf(out, "Total: %d\n", total);
	fclose(out);
}
