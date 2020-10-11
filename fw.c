#include "hash.h"

/* global vars */
# define SIZE 4000

#define DEFAULT_NWORDS 10

#define USE_ERROR "usage: fw [-n num] [ file1 [ file 2 ...] ]\n"
#define EXIST_ERROR "%s: No such file or directory\n"

char read_word(FILE *f, HashTable *hashTable) {
	/* given a file stream, returns the next word */
    char *word = NULL;
    int size = 0;
    int i = 0;
    int c;

    c = getc(f);
    while (c != EOF && c != 32 && c != 10 && c != 9) {
    	if (i > size - 2) {
    		size += SIZE;
    		word = realloc(word, size);
    		if (!word) {
    			perror("Reallocing error");
    			exit(EXIT_FAILURE);
    		}
    	}
		/*
    	if (isalpha(c) == 0) {
    		printf("not alpha char\n");
    	}
		*/
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
	FILE *f;
	char character;

	int numWords = 0;

	int nwords = DEFAULT_NWORDS;

	data **sortedData = NULL;


	HashTable *hashTable = CreateTable(SIZE);

	/* for loop for passing files */

	if (argc == 1) {
		/* read from stdin */
		character = read_word(stdin, hashTable);
		} else {

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
						printf(USE_ERROR);
						exit(EXIT_FAILURE);
					}
				}
				else
				{
					printf(USE_ERROR);
					exit(EXIT_FAILURE);
				}
				i++;
			}
			else 
			{
				f = fopen(argv[i], "r");
				if (f == NULL)
				{
					printf(EXIST_ERROR, argv[i]);
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
	}

	sortedData = sortHashTable(hashTable);

	i = 0;
	while(sortedData[i] != NULL)
	{
		numWords ++;
		i++;
	}

	printf("The top %d words (out of %d) are:\n", nwords, numWords);

	i = 0;
	while(sortedData[i] != NULL && i < nwords)
	{
		printf("%9d ", sortedData[i]->occurance);
		printf("%s\n", sortedData[i]->word);
		i++;
	}
	FreeHashTable(hashTable);
	return 0;
}
