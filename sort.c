#include "hash.h"
#include <string.h>

int comp (const void *ap, const void *bp)
{
	data *a = *(data**)ap;
	data *b = *(data**)bp;
	int c = 0;

	c = b->occurance - a->occurance;
	if(c == 0)
	{
		c = strcmp(b->word, a->word);
	}
	return c;
}

data **sortHashTable(HashTable *hashTable)
{
	int arrayIndex = 0;
	int i;
	data **dataList = NULL;

	/* for loop to create list of data */
	for(i = 0; i < hashTable->size; i ++)
	{
		if(hashTable->table[i] != NULL)
		{
			dataList = realloc(dataList,
					   (arrayIndex + 1) * sizeof(data*));

			dataList[arrayIndex] = hashTable->table[i];
			
			arrayIndex ++;
		}
	}
	qsort(dataList, arrayIndex, sizeof(data*), comp);

	dataList = realloc(dataList, (arrayIndex + 1) * sizeof(data*));
	dataList[arrayIndex] = NULL;
	return dataList;
}
