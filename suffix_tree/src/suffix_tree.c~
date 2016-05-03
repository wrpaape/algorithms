#include "suffix_tree.h"

#define EDGES_SIZE (sizeof(struct SuffixNode *) * (CHAR_MAX - 1lu))

int main(void)
{
	struct SuffixTree *suffix_tree = build_suffix_tree("rooty tooty point and shooty");

	puts("DONE");

	return 0;
}


struct SuffixSubstring *build_suffix_tree(char *string)
{
	/* preliminary scan for tree sizing */
	char *letter;
	size_t alphabet_size = 1ul; /* including '\0' */
	bool alphabet_set[CHAR_MAX] = {
		[1l ... (CHAR_MAX - 1ul)] = false
	};

	for (letter = string; *letter != '\0'; ++letter) {

		if (alphabet_set[*letter])
			continue;

		alphabet_set[*letter] = true;
		++alphabet_size;
	}


	size_t leaf_count = (size_t) (1l + letter - string);

	size_t internal_count = leaf_count - alphabet_size;



	return NULL;
}
