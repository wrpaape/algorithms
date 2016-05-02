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

	struct SuffixNode *const root = init_suffix_node(string);

	struct SuffixNode *active_node = root;

	char **upto = &(active_node->upto);

	struct SuffixEdge *active_edge = init_suffix_edge(upto);

	char key = *string;

	size_t active_length = 0ul;
	size_t rem_suffixes  = 1ul;

	active_node->edges[key] = active_edge;


	while (1) {
		++string;

		if (*string == '\0')
			return root;

		*upto = string;
		key   = *string;

		if (active_node->edges[key] != NULL) {

			active_edge = active_node->edges[key];
			++active_length;
			++remainder;
		}


		active_node->edges[*string] = active_edge;

		++(active_node->count);

		++string;

	}
}

inline struct SuffixNode *init_suffix_node(char *const restrict upto)
{
	struct SuffixNode *node;

	HANDLE_MALLOC(node, sizeof(struct SuffixNode));

	node->upto  = upto;
	node->count = 0ul;

	memset(&node->edges[1l],
	       0,
	       sizeof(struct SuffixEdge *) * (CHAR_MAX - 1ul));

	return node;
}

inline struct SuffixEdge *init_suffix_edge(char **const restrict upto)
{
	struct SuffixEdge *edge;

	HANDLE_MALLOC(edge, sizeof(struct SuffixEdge));

	edge->from = *upto;
	edge->upto = upto;

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
