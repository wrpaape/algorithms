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

	return start;
}


int main(void)
{

	struct Node *node = init_graph();

	return 0;
}
