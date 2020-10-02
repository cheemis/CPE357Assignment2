#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024


typedef struct HashItemStructure data;
struct HashItemStructure
{
	int occurance;
	char *word;
};

typedef struct HashTableStructure HashTable;
struct HashTableStructure
{
	int size;
	data **table;
};

/* to create hashed data */
data *CreateDataStructure(char *word, int size);

/* to create a hash table on the heap */
HashTable *CreateTable();

/* to hash data */
int Hash(const char *word, int size);

/* to see if data exists in hash table */
data *SearchForOccurance(HashTable *hashTable, const char *word);

/* to place a word in a table, returns 1 if success */
HashTable *PlaceWord(HashTable *hashTable, char *word);

/* to place data, returns 1 if success */
int PlaceData(HashTable *hashTable, data *d);

/* add more spaces to the table */
HashTable *ReHashTable(HashTable *hashTable);

/* frees a whole table and its data */
void FreeHashTable(HashTable *hashTable);
