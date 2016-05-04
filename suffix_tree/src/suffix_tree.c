#include "suffix_tree.h"

extern inline void free_suffix_tree(struct SuffixTree *tree);

extern inline void size_suffix_tree(struct SuffixTreeNodeCount *count,
				    const char *const string);


extern inline bool string_contains(const char *const string,
				   const char *const substring);


extern inline bool suffix_tree_contains(const struct SuffixTree *const tree,
					const char *const substring);

extern inline bool rem_string_contains(const char *rem_string,
				       const char *rem_substring);

bool do_suffix_node_contains(const struct SuffixNode *const node,
			     const char *rem_substring)
{
	/* no match */
	if (node == NULL)
		return false;

	/* if 'rem_substring' was depleted with bucket access of previous
	 * edge_map, substring is completely contained */
	if (*rem_substring == '\0')
		return true;

	/* reduce remaining string by bucket character */
	++rem_substring;

	/* rem_match can never be NULL bc it does not reside in a '\0' bucket */
	const char *rem_match = node->rem_match;

	const struct SuffixNode **const restrict edge_map = node->edge_map;

	/* a NULL 'edge_map' indicates that 'node' is a leaf with a non-NULL,
	 * '\0'-terminated 'rem_match' of length >= 1 */
	if (edge_map == NULL)
		return rem_string_contains(rem_match,
					   rem_substring);


	/* otherwise 'node' is internal, traverse substring */
	const char *const next_suffix = node->suffix;

	while (rem_match < next_suffix) {

		if (*rem_match != *rem_substring)
			return false;

		++rem_match;
		++rem_substring;
	}

	/* continue to next child node */
	return do_suffix_node_contains(CHAR_GET(edge_map, *rem_substring),
				       *rem_substring);

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

	struct SuffixTreeNodeCount count;

	/* scan string prior to construction to determine memory allocation */
	size_suffix_tree(&count,
			 string);

	const size_t total_node_count = count.internal + count.external;

	struct SuffixTree *tree;
	struct SuffixNode *node;
	struct SuffixNode *internal;
	struct SuffixNode **root_map;

	/* allocate memory for all nodes and edge_maps upfront */
	HANDLE_MALLOC(node,
		      sizeof(struct SuffixNode) * total_node_count);

	/* all nodes are preceeded by an edge_map, init all maps to NULL */
	HANDLE_CALLOC(root_map,
		      CHAR_SPAN * total_node_count,
		      sizeof(struct SuffixNode *));

	/* initialize tree */
	HANDLE_MALLOC(tree,
		      sizeof(struct SuffixTree));

	tree->root_map = root_map;
	tree->nodes    = node;

	/* initialize nodes before insertion into tree */
	internal = node;

	/* if no internal nodes, skip initialization */
	if (count.internal > 0ul) {
		/* partion buffers:
		 * - split node buffer into 'internal' and 'external' sections
		 * - reserve first edge_map for 'root_map' */
		struct SuffixNode *external  = internal + count.internal;
		struct SuffixNode **next_map = root_map + CHAR_SPAN;

		/* init internal nodes:
		 * - set 'edge_map' to next available span of NULL node
		 *   pointers */
		while (1) {
			node->edge_map = next_map;
			++node;

			if (node == external)
				break;

			next_map += CHAR_SPAN;
		}
	}

	while (1) {
		/* init leaf node:
		 * - set 'suffix' pointer to ABSOLUTE suffix
		 * - set 'edge_map' to NULL */
		node->suffix   = string;
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
}
