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

void append_suffix(struct SuffixBuildState *state,
		   char *const string)
{
	struct SuffixEdge *active_node = root;
}

struct SuffixNode *create_suffix_tree(char *restrict string)
{
	struct SuffixNode *const root = init_suffix_node(string);

	struct SuffixBuildState state = {
		.act_node = root,
		.act_length = 0ul,
		.rem_suffixes = 0ul
	};

	while (1)  {
		append_suffix(&state, string);

		if (*string == '\0')
			return root;

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
	edge->children = NULL;

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
