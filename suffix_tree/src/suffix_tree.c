#include "suffix_tree.h"

#define EDGES_SIZE (sizeof(struct SuffixNode *) * (CHAR_MAX - 1lu))

int main(void)
{
	struct SuffixNode *suffix_tree = create_suffix_tree("rooty tooty point and shooty");

	puts("DONE");

	return 0;
}


struct SuffixNode *create_suffix_tree(char *string)
{
	struct SuffixNode *const root = NULL;

	return root;
}
