#ifndef BINARY_TREE_BINARY_TREE_H_
#define BINARY_TREE_BINARY_TREE_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>	/* malloc, free */
#include <stdio.h>	/* printf, (f)puts */

/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
struct Node {
	unsigned int value;
	struct Node *left;
	struct Node *right;
};

struct Node *
tree_init(struct Node *restrict *const restrict alloc,
	  const unsigned int from,
	  const unsigned int upto);

static inline int
tree_create(struct Node *restrict *const restrict root,
	    const unsigned int node_count);

void
tree_invert(struct Node *const restrict node);

void
do_tree_print(struct Node *const restrict node);

static inline void
tree_print(struct Node *const restrict node);

unsigned int
tree_length(struct Node *const restrict node);

struct Node *
do_tree_nth(struct Node *const restrict node,
	    int *const restrict acc,
	    const int n);

static inline struct Node *
tree_nth(struct Node *const restrict root,
	 const int n);

static inline void
tree_free(struct Node *const restrict node);

#endif /* ifndef BINARY_TREE_BINARY_TREE_H_ */
