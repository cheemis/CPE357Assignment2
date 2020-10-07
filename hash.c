#include <string.h>
#include "hash.h"

/* Hash function from:
 * https://stackoverflow.com/questions/7666509/hash-function-for-string
 */


int SearchForOccurance(const HashTable *hashTable, const char *word)
{
	/* This function checks to see if a word exists in the hash table
	 * If it does, then a pointer to the data is returned. Otherwise,
	 * NULL is returned */
	int i = 0;

	int hash = Hash(word, hashTable->size);
	
	/* check latter half of list for word */
	for(i = hash; i < hashTable->size; i++)
	{
		if(hashTable->table[i] == NULL || strcmp((hashTable->table[i])->word, word) == 0)
		{
			return i;
		}
	}

	for(i = 0; i < hash; i++)
	{
		if(hashTable->table[i] == NULL || strcmp((hashTable->table[i])->word, word) == 0)
		{
			return i;
		}
	}

	return -1;
}

HashTable *PlaceWord(HashTable *hashTable, char *word)
{
	/* This function places a word into a hashtable. The functions
	 * returns the final hashtable, either a new one that is
	 * larger or the old one passed into it. */

	int dataInHash = SearchForOccurance(hashTable, word);

	if (dataInHash == -1)
	{
		hashTable = ReHashTable(hashTable);
		dataInHash = SearchForOccurance(hashTable, word);
	}

	if(hashTable->table[dataInHash] == NULL)
	{
		data *newData = malloc(sizeof(data));
		newData->occurance = 1;
		newData->word = word;
		hashTable->table[dataInHash] = newData;
	}
	else
	{
		hashTable->table[dataInHash]->occurance ++;
	}
	return hashTable;
}


int PlaceData(HashTable *hashTable, data *d)
{
	/* This function places data into a hashtable. The functions
	 * returns an 1 if successful and a 0 if unsuccessful. */

	int i;
	int hash = Hash(d->word, hashTable->size);

	/* check latter half of list for NULL space */
	for(i = hash; i < hashTable->size; i++)
	{
		if(hashTable->table[i] == NULL)
		{
			hashTable->table[i] = d;
			return 1;
		}
	}
	/* check first half of list for NULL space */
	for(i = 0; i < hash; i++)
	{
		if(hashTable->table[i] == NULL)
		{
			hashTable->table[i] = d;
			return 1;
		}
	}
	return 0;
}


int Hash(const char *word, int size)
{
	/* This Function Hashes a word based on
	 * the hashtable's size. */
	int hash = 1;
	while (*word != '\0')
	{
		/* hash bitshifted to right 4 places + 
		 * current letter floor divided by size */

		/* credits go to this - http://www.cse.yorku.ca/~oz/hash.html */
		hash = ((hash << 4) + (int)(*word)) % size;
		word++;
	}
	return hash % size;
}


data *CreateDataStructure(char *word, int size)
{
	/* This Function creates a Data Structure and
	 * returns it. */
	data *d = malloc(sizeof(data));
	d->occurance = 0;
	return d;
}


HashTable *CreateTable(int size)
{
	/* This function creates a hashtable my mallocing space for
 	 * the table itself and the array of spaces inside of it.  */

	int i;
	HashTable *newHashTable = malloc(sizeof(HashTable));
	newHashTable->size = size;
	
	newHashTable->table = malloc(size * sizeof(data*));
	

	for(i = 0; i < size; i ++)
	{
		newHashTable->table[i] = NULL;
	}
	return newHashTable;
}

HashTable *ReHashTable(HashTable *hashTable)
{
	HashTable *newHashTable;

	int i;
	newHashTable = CreateTable(hashTable->size * 2);

	
	for(i = 0; i < hashTable->size; i++)
	{
		PlaceData(newHashTable, (hashTable->table[i]));
	}
	free(hashTable);
	return newHashTable;
}

void FreeHashTable(HashTable *hashTable)
{
	/* This function removes an entire hashtable and all its
 	 * elements. It should only be called at the end of the
	 * of the program. */

	int i;
	for(i = 0; i < hashTable->size; i++)
	{
		if(hashTable->table[i] != NULL)
		{
			free(hashTable->table[i]->word);
			free(hashTable->table[i]);
		}
	}
	free(hashTable);
}

struct tuple
{
	int occurance;
	char word[30];
};

static int count = 0;

void addTupleToList (int val, char *word, struct tuple tuples[]) {
	printf("Adding '%s', mapped to %d\n", word, val);
    strcpy(tuples[count].word, word);
    tuples[count++].occurance = val;
}

void TurnHashTableToList(HashTable *hashTable, struct tuple tuples[])
{
	int i;
	for(i = 0; i < hashTable->size; i++)
	{	
		char str[5] = "test";
		char *ptr = str;
		/* if(hashTable->table[i] != NULL) */
		addTupleToList(i, ptr, tuples);
	}
}

