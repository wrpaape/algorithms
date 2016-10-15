#include "binary_tree.h"

int
main(void)
{
	struct Node *restrict root;

	const int exit_status = tree_create(&root,
					    20u);

	if (exit_status == 0u) {
		tree_print(root);
		tree_invert(root);
		tree_print(root);
		printf("tree_length: %u\n", tree_length(root));
		tree_free(root);

	} else {
		puts("tree_create failed");
	}

	return exit_status;
}

struct Node *
tree_init(struct Node *restrict *const restrict alloc,
	  const unsigned int from,
	  const unsigned int until)

{
	if (from == until)
		return NULL;

	struct Node *const restrict node = *alloc;
	++(*alloc);

	node->value = from + ((until - from) / 2u);

	node->left  = tree_init(alloc,
				from,
				node->value);
	node->right = tree_init(alloc,
				node->value + 1u,
				until);
	return node;
}

static inline int
tree_create(struct Node *restrict *const restrict root,
	    const unsigned int node_count)
{
	struct Node *restrict alloc;

	if (node_count == 0u) {
		*root = NULL;
		return 0u;
	}

	alloc = malloc(sizeof(struct Node) * node_count);

	if (alloc == NULL)
		return 1;

	*root = tree_init(&alloc,
			  0u,
			  node_count);
	return 0;
}

void
tree_invert(struct Node *const restrict node)
{
	if (node != NULL) {
		struct Node *const restrict tmp = node->left;
		node->left  = node->right;
		node->right = tmp;

		tree_invert(tmp);
		tree_invert(node->left);
	}
}

void
do_tree_print(struct Node *const restrict node)
{
	if (node != NULL) {
		do_tree_print(node->left);
		printf("- %d -", node->value);
		do_tree_print(node->right);
	}
}

static inline void
tree_print(struct Node *const restrict node)
{
	fputs("X -", stdout);
	do_tree_print(node);
	fputs("- X\n", stdout);
}

unsigned int
tree_length(struct Node *const restrict node)
{
	return (node == NULL)
	     ? 0u
	     : (1u + tree_length(node->left) + tree_length(node->right));
}

static inline void
tree_sort(struct Node *const restrict root);

static inline void
tree_free(struct Node *const restrict node)
{
	free(node);
}
