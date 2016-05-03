#include "suffix_tree.h"

/* maximum unique characters (including '\0') */
#define CHAR_SPAN (CHAR_MAX + 1ul)

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
	bool alphabet_set[CHAR_SPAN] = {
		[1l ... CHAR_MAX] = false
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

	struct SuffixNode **root_map;
	struct SuffixNode **map_buff;
	struct SuffixNode *int_buff;
	struct SuffixNode *ext_buff;

	/* allocate memory for all nodes and edge_maps upfront */
	HANDLE_MALLOC(ext_buff,
		      sizeof(struct SuffixNode) * tot_node_cnt);

	/* all nodes are preceeded by an edge_map, init all maps to NULL */
	HANDLE_CALLOC(root_map,
		      CHAR_SPAN * tot_node_cnt,
		      sizeof(struct SuffixNode *));

	/* partion buffers:
	/* - split node buffer into 'external' and 'internal' halves */
	/* - reserve first edge_map for 'root_map' */
	int_buff = &ext_buff[ext_node_cnt];
	map_buff = &root_map[CHAR_SPAN];


	/* initialize nodes before insertion into tree */
	ptrdiff_t i_node;

	/* leaf nodes:
	 * - set 'base' pointers to start of suffix
	 * - set 'edge_map' to NULL */
	for (i_node = 0l; i_node < ext_node_cnt; ++i_node) {
		ext_buff[i_node].base = &string[i_node];
		ext_buff[i_node].edge_map = NULL;
	}

	/* internal nodes:
	 * - set 'edge_map' to next available span of NULL node pointers */
	for (i_node = 0l; i_node < int_node_cnt; ++i_node)
		int_buff[i_node].edge_map = &map_buff[i_node * CHAR_SPAN];


	/* build suffix tree by incremental insertion of each leaf node */




	return NULL;
}
