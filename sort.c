#include "hash.h"
#include <string.h>

int comp (const void *ap, const void *bp)
{
	int a,b;
	int c = 0;


	a = ((data *)ap)->occurance;
	b = ((data *)bp)->occurance;

	c = b - a;

	if(c == 0)
	{
		printf("here\n");
		char *ac = ((data *)ap)->word;
		char *bc = ((data *)bp)->word;
		
		/* might need to swap order */
		c = strcmp(bc, ac);
	}

	return c;
}

int main(int argc, char const *argv[])
{
	/* this doesnt work but comp does */

	int i;

	data a;
	a.occurance = 2;
	a.word = "test";

	data *aPtr = &a;

	data b;
	b.occurance = 3;
	b.word = "aaa";

	data *bPtr = &b;

	data *points[2];
	points[0] = aPtr;
	points[1] = bPtr;

	for(i = 0; i < 2; i++)
	{
		printf("occurance: %d, Word: %s\n", points[i]->occurance, points[i]->word);
	}
	printf("\n");

	qsort(points, 2, sizeof(data), comp);

	for(i = 0; i < 2; i++)
	{
		printf("occurance: %d, Word: %s\n", points[i]->occurance, points[i]->word);
	}

	return 0;
}

