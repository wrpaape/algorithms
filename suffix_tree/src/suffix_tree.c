#include "suffix_tree.h"
#include <stdbool.h>

/* maximum unique characters (including '\0') */
#define CHAR_SPAN (CHAR_MAX + 1ul)

#define CHAR_GET(MAP, CHAR) MAP[(ptrdiff_t) (CHAR)]

int main(void)
{
	const char *string = "rooty tooty point and shooty";
	struct SuffixTree *suffix_tree = build_suffix_tree(string);

	puts("DONE");

	return 0;
}

void do_insert_suffix_leaf(struct SuffixNode **const restrict edge_map,
			   struct SuffixNode **restrict internal,
			   struct SuffixNode *const restrict leaf,
			   const char *rem_string)
{

	struct SuffixNode **const restrict slot = &CHAR_GET(edge_map,
							    *rem_string);
	/* TODO
	 * 3 cases:
	 * a) (trivial) leaf is inserted into empty slot
	 * b) slot belongs to an internal node
	 * c) slot belongs to another leaf node */

	if (*slot == NULL) {
		leaf->rem_match = (*rem_string == '\0')
				? NULL
				: rem_string + 1l;
		*slot = leaf;
		return;
	}

	struct SuffixNode *const restrict node = *slot;

	const char *rem_match = node->rem_match;
	const char *suffix = node->suffix;

	while (*slot != NULL) {

	}
}


struct SuffixTree *build_suffix_tree(const char *string)
{
	/* preliminary scan for tree sizing */
	const char *letter;
	size_t alphabet_size = 1ul; /* including '\0' */
	bool alphabet_set[CHAR_SPAN] = {
		[1l ... (CHAR_SPAN - 1l)] = false
	};

	for (letter = string; *letter != '\0'; ++letter) {

		if (CHAR_GET(alphabet_set, *letter))
			continue;

		CHAR_GET(alphabet_set, *letter) = true;
		++alphabet_size;
	}


	/* count of leaf (external) nodes of the form:
	 * - 'edge_map' is NULL
	 * - 'rem_match' points to start (INclusive) of remaining matching
	 *   substring
	 *	- NULL indicates absence of remainder (complete match)
	 * - 'suffix' points to ABSOLUTE suffix */
	const size_t ext_node_cnt = (size_t) (1l + letter - string);

	/* count of internal nodes of the form:
	 * - 'edge_map' is allocated
	 * - 'rem_match' points to start (INclusive) of remaining matching
	 *   substring
	 * - 'suffix' points to RELATIVE suffix
	 *	- in other words, end (EXclusive) of remaining matching
	 *	substring */
	const size_t int_node_cnt = ext_node_cnt - alphabet_size;

	/* count of all (total) nodes in tree */
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
	tree->nodes        = node;
	tree->int_node_cnt = int_node_cnt;
	tree->ext_node_cnt = ext_node_cnt;
	tree->tot_node_cnt = tot_node_cnt;

	/* initialize nodes before insertion into tree */
	internal = node;

	/* if no internal nodes, skip initialization */
	if (int_node_cnt == 0ul)
		goto INSERT_SUFFIXES;

	/* partion buffers:
	 * - split node buffer into 'internal' and 'external' sections
	 * - reserve first edge_map for 'root_map' */
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

INSERT_SUFFIXES:
	while (1) {
		/* init leaf node:
		 * - set 'suffix' pointer to ABSOLUTE suffix
		 * - set 'edge_map' to NULL */
		node->suffix     = string;
		node->edge_map = NULL;

		do_insert_suffix_leaf(root_map, &internal, node, string);

		if (*string == '\0')
			return tree;

		--string;
		++node;
	}

	return tree;
}
