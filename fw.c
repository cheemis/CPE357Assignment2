#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

/* global vars */
# define SIZE 1024
# define DEFAULT_NWORDS 10


char read_word(FILE *f, HashTable *hashTable) {
	/* given a file stream, returns the next word */
    char *word = NULL;
    int size = 0;
    int i = 0;
    int c;

    c = getc(f);
    while (c != EOF && c != 32 && c != 10) {
    	if (i > size - 2) {
    		size += SIZE;
    		word = realloc(word, size);
    		if (!word) {
    			perror("Reallocing error");
    			exit(EXIT_FAILURE);
    		}
    	}
    	if (isalpha(c) == 0) {
    		printf("not alpha char");
    	}
    	c = tolower(c);
    	word[i++] = c;
    	c = getc(f);
    }
    
    if (word)
	{
    	word[i++] = '\0';
    	hashTable = PlaceWord(hashTable, word);
    }
	
    return c;
}


int main(int argc, char const *argv[])
{
	int i;
	int nullcount = 0;
	int nwords = DEFAULT_NWORDS;
	FILE *f;
	char character;

	HashTable *hashTable = CreateTable(SIZE);

	/* for loop for passing files */
	for(i = 1; i < argc; i ++)
	{	
		if (strcmp(argv[i], "-n") == 0) {
			int n = atoi(argv[i+1]);
			if (n > 0) {
				nwords = n;
				printf("Number of words: %i\n", n);
			} else {
				perror("Error, not a number");
    			exit(EXIT_FAILURE);
			}
			i++;
		} else 
		{
			f = fopen(argv[i], "r");
			if (f == NULL)
			{
				perror("Error opening file\n");
	    	}
			else
			{
				printf("File: %s\n", argv[i]);

				do {
				character = read_word(f, hashTable);
				} while (character != EOF);

				fclose(f);
			}
		}
	}
	printf("hashed everything!\nTable: %p\tSize: %d\n", hashTable, hashTable->size);

		for(i = 0; i < hashTable->size; i ++)
		{
			if(hashTable->table[i] != NULL)
			{
				printf("Word: %s\tOccurance: %d\tAddress: %p\n", hashTable->table[i]->word, hashTable->table[i]->occurance, hashTable->table[i]);
			}
			else
			{
				nullcount ++;
			}
		}
	printf("null count in table: %d\n", nullcount);

	FreeHashTable(hashTable);

	int total = 100;

	printf("The top %i words (out of %i) are:\n", nwords, total);

	for (i=0; i<nwords; i++) {
		printf("Word");
	}

	return 0;
}
