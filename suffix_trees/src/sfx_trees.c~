#include "sfx_trees.h"

#define EDGES_SIZE (sizeof(struct SfxNode *) * (CHAR_MAX - 1lu))

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

	struct SfxNode **active_edge_ptr = &active_node->edges[*sfx];


	++(active_node->edge_count);
	active_node->upto = sfx;

	if (*active_edge_ptr == NULL) {
		*active_edge_ptr = init_sfx_edge(&active_node->upto);
		return;
	}

	char *upto = active_node->upto;


	while (1) {

		active_edge_ptr = &active_node->edges[*sfx];

		if (*active_edge_ptr == NULL)
			break;

		while ()

	}

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

inline struct SfxNode *init_sfx_node(char *const base)
{
	struct SfxNode *node;

	HANDLE_MALLOC(node, sizeof(struct SfxNode));

	node->base       = base;
	node->edge_count = 0l;
	node->rem_sfx    = NULL;
	memset(&node->edges[0l], 0, EDGES_SIZE);

	return node;
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
