#include "binary_tree.h"

#define PRINT_NTH(N)							\
node = tree_nth(root, N);						\
printf("tree_nth(" #N "): %d\n", (node == NULL) ? -1 : node->value)

#define PRINT_IS_SORTED()						\
printf("is_tree_sorted: %s\n", is_tree_sorted(root) ? "true" : "false")

int
main(void)
{
	struct Node *restrict root;
	struct Node *restrict node;

	const int exit_status = tree_create(&root,
					    20u);

	if (exit_status == 0u) {
		tree_print(root);
		PRINT_IS_SORTED();
		tree_invert(root);
		tree_print(root);
		PRINT_IS_SORTED();
		printf("tree_length: %u\n", tree_length(root));
		PRINT_NTH(0);
		PRINT_NTH(-1);
		PRINT_NTH(10);
		PRINT_NTH(19);
		PRINT_NTH(20);
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

bool
do_is_tree_sorted(const struct Node *const restrict node,
		  const unsigned int min_value,
		  const unsigned int max_value)
{
	if (node == NULL)
		return true;

	const unsigned int node_value = node->value;

	if ((node_value < min_value) || (node_value > max_value))
		return false;


	return do_is_tree_sorted(node->left,
				 min_value,
				 node_value)
	    && do_is_tree_sorted(node->right,
				 node_value,
				 max_value);
}

static inline bool
is_tree_sorted(const struct Node *const restrict root)
{
	return do_is_tree_sorted(root,
				 0,
				 UINT_MAX);
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

struct Node *
do_tree_nth(struct Node *const restrict node,
	    int *const restrict acc,
	    const int n)
{
	struct Node *restrict nth;

	if (node == NULL)
		return NULL;

	nth = do_tree_nth(node->left,
			  acc,
			  n);

	if (nth != NULL)
		return nth;

	if (*acc == n)
		return node;

	++(*acc);

	return do_tree_nth(node->right,
			   acc,
			   n);
}

static inline struct Node *
tree_nth(struct Node *const restrict root,
	 const int n)
{
	int acc = 0;

	return do_tree_nth(root,
			   &acc,
			   n);
}

static inline void
tree_free(struct Node *const restrict node)
{
	free(node);
}
