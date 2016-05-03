#include "suffix_tree.h"

#define EDGES_SIZE (sizeof(struct SuffixNode *) * (CHAR_MAX - 1lu))

int main(void)
{
	struct SuffixTree *suffix_tree = build_suffix_tree("rooty tooty point and shooty");

	puts("DONE");

	return 0;
}


struct SuffixTree *build_suffix_tree(char *string)
{
	struct SuffixTree *tree;

	HANDLE_MALLOC(tree, sizeof(struct SuffixTree));

	size_t alphabet_size = 0ul;
	bool alphabet_set = {
		[0l ... (CHAR_MAX - 1ul)] = false
	};

	char *letter = string;

	return tree;
}
