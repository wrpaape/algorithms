#include "sfx_trees.h"

int main(void)
{
	char **matches = pattern_find_all("bananas in pajamas ooga booga",
					  "ooga");

	size_t count;

	for (count = 0ul; matches[count] != NULL; ++count);

	printf("count: %zu\n", count);

	return 0;
}

void append_next_sfx(struct SfxNode **active_node_ptr,
		     char *sfx)
{

	struct SfxNode *active_node = *active_node_ptr;

	struct SfxNode **active_edge_ptr = &(active_node->edges)[*sfx];

	char **upto_ptr = &(active_node->upto);

	++(active_node->count);
	*upto_ptr = sfx;

	if (*active_edge_ptr == NULL) {
		*active_edge_ptr = init_sfx_edge(upto_ptr);
	}


	while (1) {
		active_edge_ptr = &(active_node->edges)[*sfx];

		if (*active_edge_ptr == NULL)
			break;

		while ()

	}

	active_node->upto = sfx;
	*active_node_ptr  = active_node;
}



struct SfxNode *create_sfx_tree(char *string)
{
	struct SfxNode *const root = init_sfx_node(string);

	struct SfxNode *active_node = root;

	while (*string != '\0')  {

		append_next_sfx(&active_node,
				string);

		++string;
	}

	return root;
}

inline struct SfxNode *init_sfx_node(char *const upto)
{
	struct SfxNode *node;

	HANDLE_MALLOC(node, sizeof(struct SfxNode));

	node->upto  = upto;
	node->count = 0ul;
	memset(&node->edges[1l], 0,
	       sizeof(struct SfxEdge *) * (CHAR_MAX - 1ul));

	return node;
}

inline struct SfxEdge *init_sfx_edge(char **const upto_ptr)
{
	struct SfxEdge *edge;

	HANDLE_MALLOC(edge, sizeof(struct SfxEdge));

	edge->from = *upto_ptr;
	edge->upto_ptr = upto_ptr;
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
