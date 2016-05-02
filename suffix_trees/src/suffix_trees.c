#include "suffix_trees.h"

#define INIT_SUFFIX_NODE(N) HANDLE_CALLOC(N, 1ul, sizeof(struct SuffixNode))


int main(void)
{
	char **matches = pattern_find_all("bananas in pajamas ooga booga",
					  "ooga");

	size_t count;

	for (count = 0ul; matches[count] != NULL; ++count);


	printf("count: %zu\n", count);

	return 0;
}

struct SuffixNode *create_suffix_tree(char *restrict string)
{
	if (*string == '\0')
		return NULL;

	struct SuffixNode *const root = init_suffix_node(*string);

	struct SuffixNode *active_node = root;
	struct SuffixEdge *active_edge;

	char *upto;

	do {
		active_edge = init_suffix_edge(active_node->key)
		HANDLE_MALLOC(active_edge, sizeof(struct SuffixEdge));

	} while (string != '\0');



	size_t active_length = 0ul;
	size_t rem_suffixes  = 0ul;



	return root;
}

inline struct SuffixNode *init_suffix_node(const char key)
{
	struct SuffixNode *node;

	HANDLE_MALLOC(node, sizeof(struct SuffixNode));

	memset(&node->edges[1l], 0, sizeof(struct SuffixEdge) * (CHAR_MAX - 1ul));

	node->key   = key;
	node->count = 0ul;

	return node;
}

inline struct SuffixEdge *init_suffix_edge(char *const from,
					   char *const upto)
{
	struct SuffixEdge *edge;

	HANDLE_MALLOC(edge, sizeof(struct SuffixEdge));


	edge->from  = key;
	edge->count = 0ul;

	return edge;
}

/*
 * Returns a NULL terminated array of char pointers pointing to the start of
 * all occurences of 'pattern' in 'string'
 */
char **pattern_find_all(char *const restrict string,
			char *const restrict pattern)
{
	char **matches;


	return matches;
}
