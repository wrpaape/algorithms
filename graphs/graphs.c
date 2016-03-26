#include "graphs.h"

/*
 * ╔═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╗
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ║               ║ TEL4B ║ DEAD6 ║ DEAD2           TEL5B ║         TEL2B ║
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ╠══   ══╬══   ══╬══   ══╬══   ══╬═══════╬═══════╬═══════╬══   ══╬═══════╣
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ║       ║               ║ TEL3B ║         NODE1         ║         DEAD9 ║
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ╠══   ══╬═══════╬═══════╬═══════╬══   ══╬══   ══╬══   ══╬═══════╬═══════╣
 * ║       ║       ║*     *║       ║       ║       ║       ║       ║       ║
 * ║               ║ GOAL! ║               ║       ║ DEAD8 ║ TEL6B         ║
 * ║       ║       ║*     *║       ║       ║       ║       ║       ║       ║
 * ╠═══════╬══   ══╬══   ══╬══   ══╬═══════╬══   ══╬═══════╬═══════╬══   ══╣
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ║ TEL5A   NODE4         ║       ║ TEL3A ║       ║ DEAD7         ║ TEL4A ║
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ╠═══════╬═══════╬═══════╬══   ══╬══   ══╬══   ══╬═══════╬══   ══╬═══════╣
 * ║       ║       ║       ║       ║       ║*     *║       ║       ║       ║
 * ║ TEL1B ║         TEL6A ║               ║ START           NODE2   DEAD1 ║
 * ║       ║       ║       ║       ║       ║*     *║       ║       ║       ║
 * ╠══   ══╬══   ══╬═══════╬═══════╬═══════╬══   ══╬═══════╬═══════╬═══════╣
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ║       ║       ║ TEL2A   NODE6         ║       ║         NODE5         ║
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ╠══   ══╬══   ══╬═══════╬══   ══╬══   ══╬══   ══╬══   ══╬══   ══╬══   ══╣
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ║         NODE7 ║ DEAD4 ║       ║       ║       ║ DEAD3 ║       ║       ║
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ╠═══════╬══   ══╬══   ══╬══   ══╬══   ══╬══   ══╬═══════╬══   ══╬══   ══╣
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ║ DEAD5         ║               ║         NODE3                 ║ TEL1A ║
 * ║       ║       ║       ║       ║       ║       ║       ║       ║       ║
 * ╚═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╝
 */

struct Node *init_graph(void)
{
	struct Node *start, *goal,
		    *node1, *node2, *node3, *node4, *node5, *node6, *node7,
		    *tel1a, *tel2a, *tel3a, *tel4a, *tel5a, *tel6a,
		    *tel1b, *tel2b, *tel3b, *tel4b, *tel5b, *tel6b,
		    *dead1, *dead2, *dead3, *dead4,
		    *dead5, *dead6, *dead7, *dead8, *dead9;

	ININ(start, START, 3); ININ(goal,  GOAL,  0); ININ(node1, NODE1, 2);
	ININ(node2, NODE2, 2); ININ(node3, NODE3, 2); ININ(node4, NODE4, 2);
	ININ(node5, NODE5, 2); ININ(node6, NODE6, 2); ININ(node7, NODE7, 2);
	ININ(tel1a, TEL1A, 1); ININ(tel2a, TEL2A, 1); ININ(tel3a, TEL3A, 1);
	ININ(tel4a, TEL4A, 1); ININ(tel5a, TEL5A, 1); ININ(tel6a, TEL6A, 1);
	ININ(tel1b, TEL1B, 1); ININ(tel2b, TEL2B, 1); ININ(tel3b, TEL3B, 1);
	ININ(tel4b, TEL4B, 1); ININ(tel5b, TEL5B, 1); ININ(tel6b, TEL6B, 1);
	ININ(dead1, DEAD1, 0); ININ(dead2, DEAD2, 0); ININ(dead3, DEAD3, 0);
	ININ(dead4, DEAD4, 0); ININ(dead5, DEAD5, 0); ININ(dead6, DEAD6, 0);
	ININ(dead7, DEAD7, 0); ININ(dead8, DEAD8, 0); ININ(dead9, DEAD9, 0);

	int costs[]	     = {2, 3, 3};
	struct Node *nexts[] = {node2, node1, node3};

	set_edges(start, costs, nexts);


	return start;
}

void set_edges(struct Node *node, int *costs, struct Node **nexts)
{
	const int edge_count = node->edge_count;

	struct Edge *edge;

	for (int i = 0; i < edge_count; ++i) {

		HANDLE_MALLOC(edge, sizeof(struct Edge));

		edge->cost = costs[i];
		edge->next = nexts[i];

		node->edges[i] = edge;
	}
}

int main(void)
{

	struct Node *node = init_graph();

	printf("cost: %d\n", node->edges[2]->cost);

	return 0;
}
