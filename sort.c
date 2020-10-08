#include "hash.h"
#include <string.h>

int comp (const data *ap, const data *bp)
{
	int a,b;
	int c = 0;

	a = ap->occurance;
	b = bp->occurance;

	c = b - a;

	if(c == 0)
	{
		/* might need to swap order */
		c = strcmp(ap->word, bp->word);
	}
	return c;
}

data **sortHashTable(HashTable *hashTable)
{
	int dataIndex = 0;
	int i;
	data **dataList;

	/* for loop to create list of data */
	for(i = 0; i < hashTable->size; i ++)
	{
		if(hashTable->table[i] != NULL)
		{
			dataList = realloc(dataList, (dataIndex + 1) * sizeof(data*));
			dataList[dataIndex] = hashTable->table[i];
			dataIndex ++;
		}
	}
	qsort(dataList,dataIndex, sizeof(data*), comp);
	dataList = realloc(dataList, (dataIndex + 1) * sizeof(data*));
	dataList[dataIndex] = NULL;
	return dataList;
}
