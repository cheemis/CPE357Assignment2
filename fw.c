#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* global vars */
# define SIZE 1024


char *read_word(FILE *f) {
	/* given a file stream, returns the next word */
    char *word = NULL;
    int size = 0;
    int i = 0;
    int c;

    while ((c=getc(f)) != EOF && c != 32 && c != 10) {
    	if (i > size - 2) {
    		size += SIZE;
    		word = realloc(word, size);
    		if (!word) {
    			perror("Reallocing error");
    			exit(EXIT_FAILURE);
    		}
    	}
    	word[i++] = c;
    }
    word[i++] = '\0';
    return word;
}


int main() {
	FILE *f;

	f = fopen("TestInput", "r");
	if (f == NULL) {
        printf("Error opening file");
        exit(1);
    }

	int c;
	int size = 0;
	size_t i = 0;
	char *line = NULL;

	// do this in a loop
	char *word = read_word(fp);
	fputs(word, stdout);
	free(word);

		// size += SIZE;
		// line = realloc(line, size);
		// if (line == NULL) {
		// 	perror("Reallocing error");
		// }
		// fgets(line + i, size, f);

	// while (fgets(lines, sizeof(lines), fp) != NULL) {
	// 	printf("%s", lines);

	// }
	// do {

	// } while (!(feof(fp)));

   	fclose(f);

	return 0;
}




