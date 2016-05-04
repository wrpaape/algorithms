#include <utils/utils.h>

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

static inline void free_suffix_tree(struct SuffixTree *tree);

static inline void size_suffix_tree(struct SuffixTreeNodeCount *count,
				    const char *const string);

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
