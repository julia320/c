#include <stdio.h>
#include <math.h>
#include <string.h>

extern void makeWordList (char*);
extern char **getWordList ();
extern int getNumWords();
extern void compareFiles (char*, char*);


void printWordList (char *fileName)
{
	char **words;
	int i, numWords;

	makeWordList (fileName);
 	words = (char**) getWordList ();
	numWords = getNumWords ();
	printf ("Words in file %s\n", fileName);
	for (i=0; i<numWords; i++) {
  		printf ("  %s\n", words[i]);
	}
}

int main (int argc, char **argv)
{
  printWordList ("ex2test1.txt");
  printWordList ("ex2test2.txt");
  printWordList ("ex2test3.txt");
  compareFiles ("ex2test2.txt", "ex2test3.txt");
}
