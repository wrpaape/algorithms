#include "suffix_tree.h"
#include <stdbool.h>

/* maximum unique characters (including '\0') */
#define CHAR_SPAN (CHAR_MAX + 1ul)

#define CHAR_GET(MAP, CHAR) MAP[(ptrdiff_t) (CHAR)]

int main(void)
{
	const char *string = "rooty tooty point and shooty";

	struct SuffixTree *tree = build_suffix_tree(string);

	printf("tree: {\n"
	       "  int_node_cnt: %zu,\n"
	       "  ext_node_cnt: %zu,\n"
	       "  tot_node_cnt: %zu\n"
	       "}\n",
	       tree->int_node_cnt,
	       tree->ext_node_cnt,
	       tree->tot_node_cnt);

	puts("DONE");

	return 0;
}

void resolve_suffix_leaves(struct SuffixNode **const restrict bucket,
			   struct SuffixNode **restrict internal,
			   struct SuffixNode *const restrict new_leaf,
			   const char *rem_string)
{
	/* pop a blank node from the 'internal' buffer */
	struct SuffixNode *const restrict splice = *internal;
	++(*internal);

	/* set start of match */
	splice->rem_match = rem_string;

	/* leaf of longer suffix (placed earlier), accordingly 'rem_match'
	 * should never be NULL */
	struct SuffixNode *const restrict old_leaf = *bucket;
	const char *rem_match = old_leaf->rem_match;

	while (*rem_string == *rem_match) {
		++rem_string;
		++rem_match;
	}

	splice->suffix = rem_string;

	/* new suffix should terminate before old suffix ('rem_match' should
	 * never point to '\0'), reduce remaining match of old leaf by bucket
	 * character */
	old_leaf->rem_match = rem_match + 1l;

	/* insert old leaf into new 'edge_map' */
	CHAR_GET(splice->edge_map, *rem_match) = old_leaf;

	/* insert new leaf into new 'edge_map' */
	insert_new_leaf(&CHAR_GET(splice->edge_map, *rem_string),
			new_leaf,
			rem_string);

	/* replace 'old_leaf''s old 'bucket' with internal 'splice' node */
	*bucket = splice;
}

inline void insert_new_leaf(struct SuffixNode **const restrict bucket,
			    struct SuffixNode *const restrict leaf,
			    const char *const rem_string)
{
	/* reduce remaining string of length >= 2 by bucket character */
	leaf->rem_match = (*rem_string == '\0')
			? NULL
			: rem_string + 1l;

	/* insert leaf into 'edge_map' */
	*bucket = leaf;
}

void do_insert_suffix_leaf(struct SuffixNode **const restrict edge_map,
			   struct SuffixNode **restrict internal,
			   struct SuffixNode *const restrict leaf,
			   const char *rem_string)
{

	struct SuffixNode **const restrict bucket = &CHAR_GET(edge_map,
							      *rem_string);
	/* TODO
	 * 3 cases:
	 * a) (trivial) leaf is inserted into empty bucket
	 * b) bucket belongs to an internal node
	 * c) bucket belongs to another leaf node
	 *
	 * NOTE: should never run into complete match
	 * (node->rem_match != NULL) during tree
	 * construction as leaves are inserted in
	 * order of descending absolute suffix length */

	/* if open 'bucket', insert 'leaf' and return */
	if (*bucket == NULL) {
		insert_new_leaf(bucket,
				leaf,
				rem_string);
		return;
	}

	/* reduce remaining string by bucket character */
	++rem_string;


	/* if 'bucket' is occupied by a previously placed leaf node, splice
	 * is needed to resolve the collision: halt recursion and update
	 * tree accordingly */
	if ((*bucket)->edge_map == NULL) {
		resolve_suffix_leaves(bucket,
				      internal,
				      leaf,
				      rem_string);
		return;
	}

	/* otherwise 'int_node' housed in 'bucket' is internal, traverse its
	 * substring to determine if splice is needed */
	struct SuffixNode *const restrict int_node = *bucket;

	const char *rem_match	      = int_node->rem_match;
	const char *const next_suffix = int_node->suffix;

	while (1) {
		/* if 'leaf' completely matches substring, continue recursion at
		 * next 'edge_map' */
		if (rem_match == next_suffix) {
			do_insert_suffix_leaf(int_node->edge_map,
					      internal,
					      leaf,
					      rem_string);
			return;
		}

		/* if 'leaf' doesn't completely match, break to resolve with a
		 * splice */
		if (*rem_string != *rem_match)
			break;

		++rem_string;
		++rem_match;
	}

	/* pop a blank node from the 'internal' buffer */
	struct SuffixNode *const restrict splice = *internal;
	++(*internal);

	/* set 'splice' node substring */
	splice->rem_match = int_node->rem_match;
	splice->suffix    = rem_match;

	/* shorten 'int_node''s substring */
	int_node->rem_match = rem_match + 1l;

	/* insert 'leaf' into new 'edge_map' */
	insert_new_leaf(&CHAR_GET(splice->edge_map, *rem_string),
			leaf,
			rem_string);

	/* insert 'int_node' into new 'edge_map' */
	CHAR_GET(splice->edge_map, *rem_match) = int_node;

	/* replace 'int_node''s old 'bucket' with internal 'splice' node */
	*bucket = splice;
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

		/* insert suffixes of '\0'-terminated 'string' from longest to
		 * shortest */
		do_insert_suffix_leaf(root_map,
				      &internal,
				      node,
				      string);

		if (*string == '\0')
			return tree;

		--string;
		++node;
	}

	return tree;
}
