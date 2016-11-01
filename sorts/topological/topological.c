#include <stdio.h>	/* perror */
#include <stdlib.h>	/* exit */
#include <stdbool.h>	/* bool */

#define COUNT_NODES 10
#define COUNT_EDGES 16

struct Node;

struct EdgeInterval {
	struct Node *restrict *restrict from;
	struct Node *restrict *restrict until;
};

struct Node {
	char label;
	bool traversed;
	bool traversing;
	struct EdgeInterval edges;
};

struct StackNode {
	struct Node *node;
	struct StackNode *next;
};


static inline void
stack_push(struct StackNode *restrict *const restrict head,
	   struct Node *const restrict node)
{
	static struct StackNode stack_nodes[COUNT_NODES];
	static struct StackNode *restrict stack_node = &stack_nodes[0];

	stack_node->node = node;
	stack_node->next = *head;

	*head = stack_node;

	++stack_node;
}


static inline struct Node *
graph_init(void)
{
	static struct Node nodes[] = {
		[0] = { .label = 'A' },
		[1] = { .label = 'B' },
		[2] = { .label = 'C' },
		[3] = { .label = 'D' },
		[4] = { .label = 'E' },
		[5] = { .label = 'F' },
		[6] = { .label = 'G' },
		[7] = { .label = 'H' },
		[8] = { .label = 'I' },
		[9] = { .label = 'J' }
	};

	static struct Node *edges[COUNT_EDGES];

	struct Node *restrict node;
	struct Node **restrict edge;

	node = &nodes[0];
	edge = &edges[0];

#define PUSH_EDGE(LABEL) *edge = &nodes[LABEL - 'A']; ++edge;
	/* A */
	node->edges.from  = edge;
	PUSH_EDGE('B');
	PUSH_EDGE('D');
	node->edges.until = edge;
	/* B */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('C');
	PUSH_EDGE('D');
	PUSH_EDGE('E');
	node->edges.until = edge;
	/* C */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('F');
	node->edges.until = edge;
	/* D */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('E');
	PUSH_EDGE('G');
	node->edges.until = edge;
	/* E */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('C');
	PUSH_EDGE('F');
	PUSH_EDGE('G');
	node->edges.until = edge;
	/* F */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('H');
	node->edges.until = edge;
	/* G */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('I');
	node->edges.until = edge;
	/* H */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('G');
	PUSH_EDGE('J');
	node->edges.until = edge;
	/* I */
	++node;
	node->edges.from  = edge;
	PUSH_EDGE('J');
	node->edges.until = edge;
	/* J */
	++node;
	node->edges.from  = edge;
	node->edges.until = edge;
#undef PUSH_EDGE

	return &nodes[0];
}


static inline void
exit_cycle_detected(const struct Node *const restrict node)
__attribute__((noreturn));

static inline void
exit_cycle_detected(const struct Node *const restrict node)
{
	fprintf(stderr,
		"cycle detected at node '%c'\n",
		node->label);
	exit(1);
}

static inline void
print_stack(struct StackNode *restrict stack_node)
{
	if (stack_node == NULL) {
		puts("stack = {};");
		return;
	}

	printf("stack = {\n\t%c",
	       stack_node->node->label);

	while (1) {
		stack_node = stack_node->next;

		if (stack_node == NULL)
			break;

		printf(", %c",
		       stack_node->node->label);
	}

	puts("\n};");
}

void
do_topological_sort(struct Node *const restrict node,
		    struct StackNode *restrict *const restrict head)
{
	struct Node *restrict *restrict edge;

	if (node->traversing)
		exit_cycle_detected(node);

	if (!node->traversed) {
		node->traversing = true;

		for (edge = node->edges.from; edge < node->edges.until; ++edge)
			do_topological_sort(*edge,
					    head);

		stack_push(head,
			   node);

		node->traversed	 = true;
		node->traversing = false;
	}
}


static inline void
topological_sort(void)
{
	struct Node *restrict node;
	struct StackNode *restrict stack;

	stack = NULL;

	node = graph_init();
	const struct Node *const restrict node_until = node + COUNT_NODES;


	while (1) {
		do_topological_sort(node,
				    &stack);

		while (1) {
			++node;

			if (node == node_until) {
				print_stack(stack);
				return;
			}

			if (!node->traversed)
				break;
		}
	}
}






int
main(void)
{
	topological_sort();
	return 0;
}









