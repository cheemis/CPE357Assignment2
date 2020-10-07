#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/* global vars */
# define SIZE 1024


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
	FILE *f;
	char character;

	HashTable *hashTable = CreateTable(SIZE);

	/* for loop for passing files */
	for(i = 1; i < argc; i ++)
	{
		f = fopen(argv[i], "r");
		if (f == NULL)
		{
			printf("Error opening file '%s'\n", argv[i]);
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
	return 0;
}
