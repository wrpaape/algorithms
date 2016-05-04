#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_

#ifdef __cplusplus
#define restrict __restrict__
extern "C" {
#endif

#include <utils/utils.h>
#include <stdbool.h>

/* maximum unique characters (including '\0') */
#define CHAR_SPAN (CHAR_MAX + 1ul)

/* convience access macro to avoid compiler warning for char indices */
#define CHAR_GET(MAP, CHAR) MAP[(ptrdiff_t) (CHAR)]

struct SuffixTreeNodeCount {
	/* count of internal nodes of the form:
	 * - 'edge_map' is allocated
	 * - 'rem_match' points to start (INclusive) of remaining matching
	 *   substring
	 * - 'suffix' points to RELATIVE suffix
	 *	- in other words, end (EXclusive) of remaining matching
	 *	substring */
	size_t internal;
	/* count of leaf (external) nodes of the form:
	 * - 'edge_map' is NULL
	 * - 'rem_match' points to start (INclusive) of remaining matching
	 *   substring
	 *	- NULL indicates absence of remainder (complete match)
	 * - 'suffix' points to ABSOLUTE suffix */
	size_t external;
};

struct SuffixTree {
	struct SuffixNode **root_map;
	struct SuffixNode *nodes;
};

struct SuffixNode {
	const char *rem_match;
	const char *suffix;
	struct SuffixNode **edge_map;
};

struct SuffixTree *build_suffix_tree(const char *string);


inline void free_suffix_tree(struct SuffixTree *tree)
{
	free(tree->root_map);
	free(tree->nodes);
	free(tree);
}

inline void size_suffix_tree(struct SuffixTreeNodeCount *count,
			     const char *const string)
{
	const char *letter;
	size_t alphabet_size = 1ul; /* including '\0' */
	bool alphabet_set[CHAR_SPAN] = {
		[1l ... (CHAR_SPAN - 1l)] = false
	};

	/* scan string for length and count of unique letters */
	for (letter = string; *letter != '\0'; ++letter) {

		if (CHAR_GET(alphabet_set, *letter))
			continue;

		CHAR_GET(alphabet_set, *letter) = true;
		++alphabet_size;
	}

	count->external = (size_t) (1l + letter - string);
	count->internal = count->external - alphabet_size;
}


void resolve_suffix_leaves(struct SuffixNode **const restrict bucket,
			   struct SuffixNode **restrict internal,
			   struct SuffixNode *const restrict new_leaf,
			   const char *rem_string);

void do_insert_suffix_leaf(struct SuffixNode **const restrict edge_map,
			   struct SuffixNode **restrict internal,
			   struct SuffixNode *const restrict leaf,
			   const char *rem_string);

static inline void insert_new_leaf(struct SuffixNode **const restrict bucket,
				   struct SuffixNode *const restrict leaf,
				   const char *const rem_string);
#ifdef __cplusplus
}
#endif
#endif /* ifndef SUFFIX_TREE_H_ */
