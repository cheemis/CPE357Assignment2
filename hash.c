#include "hash.h"


int main(int argc, char const *argv[])
{
	printf("this\n");
	return 0;
}


data *SearchForOccurance(HashTable *hashTable, const char *word)
{
	/* This function checks to see if a word exists in the hash table
	 * If it does, then a pointer to the data is returned. Otherwise,
	 * NULL is returned */

	int i;
	int hash = Hash(word, hashTable->size);

	/* check latter half of list for word */
	for(i = hash; i < hashTable->size; i++)
	{
		if(hashTable->table[i] == NULL && (hashTable->table[i])->word == word)
		{
			return (hashTable->table[i]);
		}
	}

	for(i = 0; i < hash; i++)
	{
		if(hashTable->table[i] == NULL && (hashTable->table[i])->word == word)
		{
			return (hashTable->table[i]);
		}
	}
	return NULL;
}

HashTable *PlaceWord(HashTable *hashTable, char *word)
{
	/* This function places a word into a hashtable. The functions
	 * returns the final hashtable, either a new one that is
	 * larger or the old one passed into it. */


	data *dataInHash = SearchForOccurance(hashTable, word);
	HashTable *current = hashTable;
	

	if (dataInHash == NULL)
	{
		current = ReHashTable(hashTable);
		dataInHash = SearchForOccurance(current, word);
	}

	if(dataInHash)
	{
		dataInHash->occurance ++;
	}
	else
	{
		data *newData = malloc(sizeof(data));
		newData->occurance = 1;
		newData->word = word;
		dataInHash = newData;
	}
	return current;
}

int PlaceData(HashTable *hashTable, data *d)
{
	/* This function places data into a hashtable. The functions
	 * returns an 1 if successful and a 0 if unsuccessful. */

	int hash = Hash(d->word, hashTable->size);

	int i;
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
	
	while (*word != '\0' || *word != '\n')
	{
		/* hash bitshifted to right 4 places + 
		 * current letter floor divided by size */
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

	HashTable *newHashTable = malloc(sizeof(HashTable));
	newHashTable->size = size;
	
	newHashTable->table = malloc(size * sizeof(data*));
	
	int i;
	for(i = 0; i < size; i ++)
	{
		newHashTable->table[i] = NULL;
	}
	return newHashTable;
}

HashTable *ReHashTable(HashTable *hashTable)
{
	HashTable *newHashTable;
	newHashTable = CreateTable(hashTable->size * 2);

	int i;
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
			free(hashTable->table[i]);
		}
	}
	free(hashTable);
}





main ()
{
	// open stream

	// get first file
	// T
	while(file != NULL)
	{
		character = getchar(f); 
		while(character != EOF)
		{
			char *word
			word = readlongline();
			StoreInHashTable(word);
			character = getchar();
		}
		file = nextfile;
	}
}


