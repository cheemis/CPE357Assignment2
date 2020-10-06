#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/* global vars */
# define SIZE 1024


char read_word(FILE *f, HashTable hashTable) {
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
    
    if (word) {
    	word[i++] = '\0';
    	PlaceWord(&hashTable, word);
		
    	/* remove me */
    	fputs(word, stdout);
		printf("\n");
    }
	
    return c;
}


int main() {
	FILE *f;
	char character;

	HashTable hashTable = *CreateTable(SIZE);

	f = fopen("TestInput", "r");
	if (f == NULL) {
        printf("Error opening file");
        exit(1);
    }

	do {
		character = read_word(f, hashTable);
	} while (character != EOF);

	fclose(f);


	return 0;
}





