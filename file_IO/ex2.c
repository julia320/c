#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Global Variables
char* str;
char** arr;
int numWords, chcount, i, j;


// Makes an array out of the words in a file
void makeWordList (char* fileName)
{
	FILE *inputFile; 
	char ch;
	chcount = 0;
	numWords = 0;
	char buffer[256];
	int lineNum = 0;

	arr = (char**)malloc(sizeof(char*)*16);

	// Read the file and get a character
	inputFile = fopen (fileName, "r");
	ch = fgetc(inputFile);

	// Put each word into the array until reaching the end of the file
	while (ch != EOF ) {

		// If the character is a space or new line, then make a new array element for it
		if (ch == ' ' || ch == '\n' ) {
			// If the character count is 0, then there is no new string to add
			if(chcount > 0) {
				str = (char*)malloc(sizeof(char)*chcount+1);
				for (i=0; i<chcount; i++) {
					str[i] = buffer[i];
				}
				str[chcount] = '\0'; // end with a null character to indicate the end of the string
				arr[numWords] = str;
				numWords++;
				chcount = 0;
			} 
		} 

		// If an actual letter or number, add it to the buffer array
		else {
			buffer[chcount] = ch;
			chcount++;
		}

		// Read the next character
		ch = fgetc(inputFile);
	}
	fclose (inputFile);
} 

// Returns the array of words
char** getWordList ()
{
	return arr;
}

// Returns the number of words in the array
int getNumWords ()
{
	return numWords;
}


// Compares 2 files to see if they have any matching words
void compareFiles (char* fileName1, char* fileName2)
{		
	char **list1;
	char **list2;
	int a, numWords1, numWords2, greaterWords, leastWords, whichisGreater, lineNum1, lineNum2;


	// Make list1
	makeWordList(fileName1);
	list1 = getWordList();
	numWords1 = getNumWords();
	
	// Make list2
	makeWordList(fileName2);
	list2 = getWordList();
	numWords2 = getNumWords();


	// Determine which list has more words, use that # in the loop
	if (numWords1 > numWords2) {
		greaterWords = numWords1;
		leastWords = numWords2;
		whichisGreater = 1;
	}
	else {
		greaterWords = numWords2;
		leastWords = numWords1;
		whichisGreater = 2;
	}

	
	// Set line counts to start at 1
	lineNum1 = 1;
	lineNum2 = 1;

	// Compare lists 1 and 2 and print accordingly 
	for (a=0; a<greaterWords; a++) {

		if(a >= leastWords ) {
                	// don't compare, at least one list has been exhausted
			if (whichisGreater==2) {
				printf("Word #%d:\nFile %s has been exhausted.\nOn line %d in file %s: %s\n\n", a, fileName1, lineNum2, fileName2, list2[a]);
			}
			else if (whichisGreater==1) {
				printf("Word #%d:\nOn line %d in file %s: %s\nFile %s has been exhausted.\n\n", a, lineNum1, fileName1, list1[a], fileName2);
			}
			break;
		}

		// If strings are the same
		else if (strcmp(list1[a],list2[a]) == 0) {
			printf("Word #%d: same in each file\nOn line %d in file %s: %s\nOn line %d in file %s: %s\n\n", a, lineNum1, fileName1, list1[a], lineNum2, fileName2, list2[a]);
		}

		// If strings are different
		else { 
			printf("Word #%d: \nOn line %d in file %s: %s \nOn line %d in file %s: %s\n\n", a, lineNum1, fileName1, list1[a], lineNum2, fileName2, list2[a]);
		}
	}

	// Free everything
	for (i=0; i<getNumWords(); i++) {
		free(str);
		free(arr[i]);
	}
	free(list1);
	free(list2);
}
