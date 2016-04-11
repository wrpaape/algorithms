#include "utils/utils.h"
#include "utils/rand.h"
#include "tree_compare.h"

void run_tree_compare(void)
{
	puts("ooga booga");

	struct BTreeNode *root1 = init_tree1();

	printf("%s\n",
	       similar_binary_trees(root1, root1) ?  "similar" : "different");

	free_tree(root1);
}

bool similar_binary_trees(struct BTreeNode *node1,
			  struct BTreeNode *node2)
{

	if (node1 == NULL)
		return node2 == NULL;

	if (node1->value != node2->value)
		return false;

	return (similar_binary_trees(node1->l_child, node2->l_child)  &&
		similar_binary_trees(node1->r_child, node2->r_child))
	    || (similar_binary_trees(node1->l_child, node2->r_child)  &&
		similar_binary_trees(node1->r_child, node2->l_child));
}

/*
 *		┌────── 0 ──────┐
 *	┌──────	1 ──────┐	2
 *	3	┌────── 4
 *		5
 */

struct BTreeNode *init_tree1(void)
{
	struct BTreeNode *nodes[6];

	for (int i = 0; i < 6; ++i) {
		HANDLE_MALLOC(nodes[i], sizeof(struct BTreeNode));
		nodes[i]->value = i;
	}

	nodes[0]->l_child = nodes[1]; nodes[0]->r_child = nodes[2];
	nodes[1]->l_child = nodes[3]; nodes[1]->r_child = nodes[4];
	nodes[2]->l_child = NULL;     nodes[2]->r_child = NULL;
	nodes[3]->l_child = NULL;     nodes[3]->r_child = NULL;
	nodes[4]->l_child = nodes[5]; nodes[4]->r_child = NULL;
	nodes[5]->l_child = NULL;     nodes[5]->r_child = NULL;

	return nodes[0];
}

inline void free_tree(struct BTreeNode *root)
{
	if (root == NULL)
		return;

	free_tree(root->l_child);
	free_tree(root->r_child);
	free(root);
}
