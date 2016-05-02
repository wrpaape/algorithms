#include "suffix_trees.h"


int main(void)
{
	char **matches = pattern_find_all("bananas in pajamas ooga booga", "ooga");

	size_t count;

	for (count = 0ul; matches[count] != NULL; ++count);


	printf("count: %zu\n", count);

	return 0;
}

/*
 * Returns a NULL terminated array of char pointers pointing to the start of
 * all occurences of 'pattern' in 'string'
 */
char **pattern_find_all(char *const restrict string,
			char *const restrict pattern)
{
	char **matches;


	return matches;
}
