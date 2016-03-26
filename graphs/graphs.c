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
		    *dead1, *dead2, *dead3, *dead4, *dead5, *dead6, *dead7,
		    *dead8, *dead9;

	INIT(start, START, 3); INIT(goal,  GOAL,  0); INIT(node1, NODE1, 2);
	INIT(node2, NODE2, 2); INIT(node3, NODE3, 2); INIT(node4, NODE4, 2);
	INIT(node5, NODE5, 2); INIT(node6, NODE6, 2); INIT(node7, NODE7, 2);
	INIT(tel1a, TEL1A, 1); INIT(tel2a, TEL2A, 1); INIT(tel3a, TEL3A, 1);
	INIT(tel4a, TEL4A, 1); INIT(tel5a, TEL5A, 1); INIT(tel6a, TEL6A, 1);
	INIT(tel1b, TEL1B, 1); INIT(tel2b, TEL2B, 1); INIT(tel3b, TEL3B, 1);
	INIT(tel4b, TEL4B, 1); INIT(tel5b, TEL5B, 1); INIT(tel6b, TEL6B, 1);
	INIT(dead1, DEAD1, 0); INIT(dead2, DEAD2, 0); INIT(dead3, DEAD3, 0);
	INIT(dead4, DEAD4, 0); INIT(dead5, DEAD5, 0); INIT(dead6, DEAD6, 0);
	INIT(dead7, DEAD7, 0); INIT(dead8, DEAD8, 0); INIT(dead9, DEAD9, 0);

	SET_EDGES(start, WRAP({2, 3, 3}),	WRAP({node2, node1, node3}));
	SET_EDGES(node1, WRAP({2, 7}),		WRAP({dead8, tel3a}));
	SET_EDGES(node2, WRAP({1, 2}),		WRAP({dead1, dead7}));
	SET_EDGES(node3, WRAP({4, 4}),		WRAP({node5, node6}));
	SET_EDGES(node4, WRAP({1, 2}),		WRAP({tel5a, goal }));
	SET_EDGES(node5, WRAP({2, 3}),		WRAP({dead3, tel1a}));
	SET_EDGES(node6, WRAP({1, 4}),		WRAP({tel2a, dead4}));
	SET_EDGES(node7, WRAP({2, 3}),		WRAP({dead5, tel6a}));
	SET_EDGES(tel1a, WRAP({TELEPORT_COST}), WRAP({tel1b}));
	SET_EDGES(tel2a, WRAP({TELEPORT_COST}), WRAP({tel2b}));
	SET_EDGES(tel3a, WRAP({TELEPORT_COST}), WRAP({tel3b}));
	SET_EDGES(tel4a, WRAP({TELEPORT_COST}), WRAP({tel4b}));
	SET_EDGES(tel5a, WRAP({TELEPORT_COST}), WRAP({tel5b}));
	SET_EDGES(tel6a, WRAP({TELEPORT_COST}), WRAP({tel6b}));
	SET_EDGES(tel1b, WRAP({3}),		WRAP({node7}));
	SET_EDGES(tel2b, WRAP({3}),		WRAP({dead9}));
	SET_EDGES(tel3b, WRAP({1}),		WRAP({dead6}));
	SET_EDGES(tel4b, WRAP({7}),		WRAP({node4}));
	SET_EDGES(tel5b, WRAP({2}),		WRAP({dead2}));
	SET_EDGES(tel6b, WRAP({2}),		WRAP({tel4a}));

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

	while (1) {
	}

	printf("cost: %d\n", node->edges[2]->cost);

	return 0;
}
