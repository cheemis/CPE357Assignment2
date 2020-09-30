#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024


typedef struct HashItemStructure data;
struct HashItemStructure
{
	int occurance;
	int key;
	char *word;
};

typedef struct HashTableStructure HashTable;
struct HashTableStructure
{
	int size;
	data **table;
};

/* to create hashed data */
data CreateData(char *word, int size);

/* to create a hash table on the heap */
HashTable *CreateTable();

/* to hash data */
int Hash(const char *word, int size);

/* to see if data exists in hash table */
data *Search(int key);

/* to place data, returns 1 if success */
int PlaceData(data);

/* add more spaces to the table */
HashTable *ReHashTable(HashTable hashTable);


int main()
{
	return 0;
}


int Hash(const char *word, int size)
{
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


data CreateData(char *word, int size)
{
	data d;
	d.occurance = 0;
	d.key = Hash(word, size);
	return d;
}

/* This function creates a hashtable my mallocing space for
 * the table itself and the array of spaces inside of it  */
HashTable *CreateTable()
{
	HashTable *newHashTable = malloc(sizeof(HashTable));
	newHashTable->size = SIZE;
	
	newHashTable->table = malloc(SIZE * sizeof(data*));
	
	int i;
	for(i = 0; i < SIZE; i ++)
	{
		newHashTable->table[i] = NULL;
	}
	return newHashTable;
}
