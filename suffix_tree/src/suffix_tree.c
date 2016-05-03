#include "suffix_tree.h"

int main(void)
{
	struct SuffixTree *suffix_tree = build_suffix_tree("rooty tooty point and shooty");

	puts("DONE");

	return 0;
}


struct SuffixTree *build_suffix_tree(char *string)
{
	/* preliminary scan for tree sizing */
	char *letter;
	size_t alphabet_size = 1ul; /* including '\0' */
	bool alphabet_set[CHAR_MAX] = {
		[1l ... (CHAR_MAX - 1l)] = false
	};

	for (letter = string; *letter != '\0'; ++letter) {

		if (alphabet_set[*letter])
			continue;

		alphabet_set[*letter] = true;
		++alphabet_size;
	}


	/* count of leaf nodes with a NULL edge_map */
	const size_t ext_node_cnt = (size_t) (1l + letter - string);

	/* count of internal nodes with a non-NULL edge_map */
	const size_t int_node_cnt = ext_node_cnt - alphabet_size;

	/* count of all nodes in tree */
	const size_t tot_node_cnt = ext_node_cnt + int_node_cnt;

	struct SuffixSubstring **map_buff;
	struct SuffixSubstring *node_buff;

	/* all nodes are preceeded by an edge_map */
	HANDLE_CALLOC(map_buff,
		      CHAR_MAX * tot_node_cnt,
		      sizeof(struct SuffixSubstring *));


	return NULL;
}
