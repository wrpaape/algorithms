#include "suffix_trees.h"


extern inline void free_match(struct Match *match);


int main(void)
{
	puts("OOGA BOOGA");

	return 0;
}

/*
 * returns a 'Match' struct of the form:
 *
 * struct Match {
 *	ptrdiff_t *indices;	a pointer to an array of indices of all occurences of 'pattern' in 'string'
 *	size_t count;		count of all matches (length of 'indices')
 *};
 */
struct Match *find_pattern(char *const restrict string,
			   char *const restrict pattern)
{

	ptrdiff_t *indices = NULL;

	return indices;
}
