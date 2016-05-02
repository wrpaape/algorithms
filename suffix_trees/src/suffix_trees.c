#include "suffix_trees.h"


int main(void)
{
	char **matches = pattern_find_all("bananas in pajamas ooga booga", "ooga");

	size_t count;

	for (count = 0ul; matches[count] != NULL; ++count);


	printf("count: %zu\n", count);

	return 0;
}

struct SuffixNode **create_suffix_tree(char *const restrict string)
{
	/* init alphabet */
	size_t char_counts[CHAR_MAX] = { [0 ... (CHAR_MAX - 1)] = 0ul };
	size_t uniq_chars = 0ul;

	for (char *char_ptr = string; *char_ptr != '\0'; ++char_ptr)
		++char_counts[*char_ptr];

	for (char key = CHAR_MAX; key >= '\0'; --key) {
		if (char_counts[key] > 0ul)
			++uniq_chars;
	}




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
