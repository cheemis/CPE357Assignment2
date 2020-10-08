#include "hash.h"

/* global vars */
# define SIZE 1024

#define DEFAULT_NWORDS 10

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
	FILE *f;
	char character;

	int numWords = 0;

	int nwords = DEFAULT_NWORDS;

	data **sortedData = NULL;


	HashTable *hashTable = CreateTable(SIZE);

	/* for loop for passing files */
	for(i = 1; i < argc; i ++)
	{	
		if (strcmp(argv[i], "-n") == 0)
		{
			if(i + 1 < argc)
			{
				int n = atoi(argv[i+1]);
				if (n >= 0)
				{
					nwords = n;
				}
				else
				{
					perror("Error, not a number or negative number");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				perror("Error, no number specified");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		else 
		{
			f = fopen(argv[i], "r");
			if (f == NULL)
			{
				perror("Error opening file\n");
	    	}
			else
			{
				do {
				character = read_word(f, hashTable);
				} while (character != EOF);

				fclose(f);
			}
		}
	}

	sortedData = sortHashTable(hashTable);

	i = 0;
	while(sortedData[i])
	{
		numWords ++;
		i++;
	}

	printf("The top %d words (out of %d) are:\n", nwords, numWords);

	i = 0;
	while(sortedData[i] != NULL && i < nwords)
	{
		printf("\t %d %s\n", sortedData[i]->occurance, sortedData[i]->word);
		i++;
	}
	
	FreeHashTable(hashTable);
	return 0;
}
