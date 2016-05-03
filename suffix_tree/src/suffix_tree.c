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

	struct SuffixTree *tree;
	struct SuffixNode **root_map;
	struct SuffixNode *internal;
	struct SuffixNode *node;

	/* allocate memory for all nodes and edge_maps upfront */
	HANDLE_MALLOC(node,
		      sizeof(struct SuffixNode) * tot_node_cnt);

	/* all nodes are preceeded by an edge_map, init all maps to NULL */
	HANDLE_CALLOC(root_map,
		      CHAR_SPAN * tot_node_cnt,
		      sizeof(struct SuffixNode *));

	/* initialize tree */
	HANDLE_MALLOC(tree,
		      sizeof(struct SuffixTree));

	tree->root_map     = root_map;
	tree->node_buff    = node;
	tree->int_node_cnt = int_node_cnt;
	tree->ext_node_cnt = ext_node_cnt;
	tree->tot_node_cnt = tot_node_cnt;

	/* initialize nodes before insertion into tree */
	internal = node;

	/* if no internal nodes, skip initialization */
	if (int_node_cnt == 0ul)
		goto INIT_LEAF_NODES;

	/* partion buffers:
	/* - split node buffer into 'internal' and 'external' sections
	/* - reserve first edge_map for 'root_map' */
	struct SuffixNode *external  = internal + int_node_cnt;
	struct SuffixNode **next_map = root_map + CHAR_SPAN;

	/* internal nodes:
	 * - set 'edge_map' to next available span of NULL node pointers */
	while (1) {
		node->edge_map = next_map;
		++node;

		if (node == external)
			break;

		next_map += CHAR_SPAN;
	}

INIT_LEAF_NODES:
	/* leaf nodes:
	 * - set 'base' pointers to start of suffix
	 * - set 'edge_map' to NULL */
	for (i = 0l; i < ext_node_cnt; ++i) {
		ext_nodes[i].base = &string[i];
		ext_nodes[i].edge_map = NULL;


	}

	return tree;
}
