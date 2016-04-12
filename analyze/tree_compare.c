#include "utils/utils.h"
#include "utils/rand.h"
#include "tree_compare.h"

void run_tree_compare(void)
{
	struct BTree *tree1 = init_tree1();
	struct BTree *tree2 = init_tree2();
	struct BTree *tree3 = init_tree3();
	struct BTree *tree4 = init_tree4();
	struct BTree *tree5 = init_tree5();
	struct BTree *tree6 = init_tree6();
	struct BTree *tree7 = init_tree7();

	compare_trees(tree1, tree2);
	compare_trees(tree1, tree3);
	compare_trees(tree1, tree4);
	compare_trees(tree1, tree5);
	compare_trees(tree1, tree6);
	compare_trees(tree1, tree7);

	free_tree(tree1);
	free_tree(tree2);
	free_tree(tree3);
	free_tree(tree4);
	free_tree(tree5);
	free_tree(tree6);
	free_tree(tree7);
}


bool inspect_similar_trees(struct BTreeNode *node1,
			   struct BTreeNode *node2,
			   struct CostAcc *costs)
{
	if (node1 == NULL)
		return node2 == NULL;

	if (node2 == NULL)
		return false;

	if (node1->value != node2->value)
		return false;

	return (similar_trees(node1->l_child, node2->l_child)
	    &&  similar_trees(node1->r_child, node2->r_child))
	    || (similar_trees(node1->l_child, node2->r_child)
	    &&  similar_trees(node1->r_child, node2->l_child));
}

/*
 * TRIVIAL CASE A (best/least expensive):
 *
 *	conditions:
 *
 *		- node1 pointer is NULL
 *		or
 *		- node2 pointer is NULL
 *
 *
 *	overhead:
 *
 *		C₀	(1)  copy parameter 'node1'
 *		C₀	(2)  copy parameter 'node2'
 *		C₁	(3)  call function
 *		C₂	(4)  compare node1 with NULL
 *		C₂	(5)  compare node2 with NULL
 *		C₅	(6)  return control to previous stack frame
 *
 *	ΣC_nodes = 2C₀ + C₁ + 2C₂ + C₅
 *		 = CA
 *
 *
 * TRIVIAL CASE B:
 *
 *	conditions:
 *
 *		- node1 pointer is valid
 *		- node2 pointer is valid
 *		- node1->value != node2->value
 *
 *	overhead:
 *
 *		C₀	(1)  copy parameter 'node1'
 *		C₀	(2)  copy parameter 'node2'
 *		C₁	(3)  call function
 *		C₂	(4)  compare node1 with NULL
 *		C₂	(5)  compare node2 with NULL
 *		C₃	(6)  deference node1 pointer
 *		C₄	(7)  access node1 field 'value'
 *		C₃	(8)  deference node2 pointer
 *		C₄	(9)  access node2 field 'value'
 *		C₂	(10) compare node1->value with node2->value
 *		C₅	(11) return control to previous stack frame
 *
 *	ΣC_nodes = 2C₀ + C₁ + 3C₂ + 2C₃ + 2C₄ + C₅
 *		 = TA  + C₂ + 2C₃ + 2C₄
 *		 = TB
 *
 *
 *
 * RECURSIVE CASE A:
 *
 *	conditions:
 *
 *		- node1 pointer is valid
 *		- node2 pointer is valid
 *		- node1->value == node2->value
 *		- node1->l_child is NULL
 *		- node2->l_child is NULL
 *		- node1->r_child is NULL
 *		- node2->r_child is NULL
 *
 *	overhead:
 *
 *		C₀	(1)  copy parameter 'node1'
 *		C₀	(2)  copy parameter 'node2'
 *		C₁	(3)  call function
 *		C₂	(4)  compare node1 with NULL
 *		C₂	(5)  compare node2 with NULL
 *		C₃	(6)  deference node1 pointer
 *		C₄	(7)  access node1 field 'value'
 *		C₃	(8)  deference node2 pointer
 *		C₄	(9)  access node2 field 'value'
 *		C₂	(10) compare node1->value with node2->value
 *		C₃	(11) deference node1 pointer
 *		C₄	(12) access node1 field 'l_child'
 *		C₃	(13) deference node2 pointer
 *		C₄	(14) access node2 field 'l_child'
 *		TA	(15) TRIVIAL CASE A
 *		C₃	(16) deference node1 pointer
 *		C₄	(17) access node1 field 'r_child'
 *		C₃	(18) deference node2 pointer
 *		C₄	(19) access node2 field 'r_child'
 *		TA	(20) TRIVIAL CASE A
 *		C₅	(21) return control to previous stack frame
 *
 *	ΣC_nodes = 2C₀ + C₁ + 3C₂ + 6C₃ + 6C₄ + C₅ + ΣC_children
 *		 = 3TA + C₂ + 6C₃ + 6C₄
 *		 = RA
 *
 *
 * RECURSIVE CASE B (worst/most expensive):
 *
 *	conditions:
 *
 *		- node1 pointer is valid
 *		- node2 pointer is valid
 *		- node1->value == node2->value
 *		- node1->l_child is valid
 *		- node2->l_child is valid
 *		- node1->r_child is valid
 *		- node2->r_child is valid
 *
 *		- node1->l_child is     similar to node2->l_child
 *		- node1->r_child is NOT similar to node2->r_child
 *		- node1->l_child is     similar to node2->r_child
 *		- node1->r_child is NOT similar to node2->l_child (implied)
 *
 *
 *	overhead:
 *
 *		C₀	(1)  copy parameter 'node1'
 *		C₀	(2)  copy parameter 'node2'
 *
 *		C₁	(3)  call function
 *
 *		C₂	(4)  compare node1 with NULL
 *		C₂	(5)  compare node2 with NULL
 *
 *		C₃	(6)  deference node1 pointer
 *		C₄	(7)  access node1 field 'value'
 *		C₃	(8)  deference node2 pointer
 *		C₄	(9)  access node2 field 'value'
 *
 *		C₂	(10) compare node1->value with node2->value
 *
 *		C₃	(11) deference node1 pointer
 *		C₄	(12) access node1 field 'l_child'
 *		C₃	(13) deference node2 pointer
 *		C₄	(14) access node2 field 'l_child'
 *
 *			(15) repeat for left children
 *
 *		C₃	(16) deference node1 pointer
 *		C₄	(17) access node1 field 'r_child'
 *		C₃	(18) deference node2 pointer
 *		C₄	(19) access node2 field 'r_child'
 *
 *			(20) repeat for right children
 *
 *		C₃	(21) deference node1 pointer
 *		C₄	(22) access node1 field 'l_child'
 *		C₃	(23) deference node2 pointer
 *		C₄	(24) access node2 field 'r_child'
 *
 *			(25) repeat for swapped children
 *
 *		C₃	(26) deference node1 pointer
 *		C₄	(27) access node1 field 'r_child'
 *		C₃	(28) deference node2 pointer
 *		C₄	(29) access node2 field 'l_child'
 *
 *			(30) repeat steps for swapped children
 *
 *		C₅	(31) return control to previous stack frame
 *
 *	ΣC_nodes = 2C₀ + C₁ + 3C₂ + 10C₃ + 10C₄ + C₅ + ΣC₍₁₅₎ + ΣC₍₂₀₎ + ΣC₍₂₅₎ + ΣC₍₃₀₎
 *		 = C_MIN + C₂ + 10C₃ + 10C₄ + 4ΣC_children
 *		 = C_MAX + 4ΣC_children
 *
 *
 *
 * CONDITIONS FOR GREATEST OVERHEAD (HYPOTHESIS):
 *
 *	- comparing perfect trees (all levels full) that are identical in value
 *	  excluding the farthest right node of the bottom level
 *
 * ie:
 *         ┌──────── 0 ────────┐           │          ┌──────── 0 ────────┐
 *    ┌─── 1 ───┐         ┌─── 2 ───┐      │     ┌─── 1 ───┐         ┌─── 2 ───┐
 * ┌─ 3 ─┐   ┌─ 4 ─┐   ┌─ 5 ─┐   ┌─ 6 ─┐   │  ┌─ 3 ─┐   ┌─ 4 ─┐   ┌─ 5 ─┐   ┌─ 6 ─┐
 * 7     8   9     10  11    12  13    14  │  7     8   9     10  11    12  13    14
 *
 *	when child pointers are NULL (recursion bottoms out)...
 *
 *	ΣC_parent = C_MAX + 2ΣC_children
 *		  = C_MAX + 2C_MIN
 *
 *	in a perfect tree, child pointers will be NULL for every leaf node
 *
 */
bool similar_trees(struct BTreeNode *node1,
		   struct BTreeNode *node2)
{
	if (node1 == NULL)
		return node2 == NULL;

	if (node2 == NULL)
		return false;

	if (node1->value != node2->value)
		return false;

	return (similar_trees(node1->l_child, node2->l_child)
	    &&  similar_trees(node1->r_child, node2->r_child))
	    || (similar_trees(node1->l_child, node2->r_child)
	    &&  similar_trees(node1->r_child, node2->l_child));
}

inline void compare_trees(struct BTree *tree1,
			  struct BTree *tree2)
{
	printf("================================\n"
	       "%s (%s nodes and depth of %s):\n"
	       "%s\n\n"
	       "is **%s**\n\n"
	       "%s (%s nodes and depth of %s):\n"
	       "%s\n"
	       "================================\n",
	       tree1->name,
	       tree1->count,
	       tree1->depth,
	       tree1->display,
	       similar_trees(tree1->root, tree2->root) ?
	       "SIMILAR TO" : "DIFFERENT THAN",
	       tree2->name,
	       tree2->count,
	       tree2->depth,
	       tree2->display);
}

struct BTree *init_tree1(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6ul);

	set_children(nodes[0], nodes[1], nodes[2]);
	set_children(nodes[1], nodes[3], nodes[4]);
	set_children(nodes[2], NULL,	 NULL);
	set_children(nodes[3], NULL,	 NULL);
	set_children(nodes[4], nodes[5], NULL);
	set_children(nodes[5], NULL,	 NULL);

	return build_tree("Binary Tree 1",
			  "        ┌────── 0 ──────┐\n"
			  "┌────── 1 ──────┐       2\n"
			  "3       ┌────── 4\n"
			  "        5",
			  "6", "4", nodes[0]);
}

struct BTree *init_tree2(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6ul);

	set_children(nodes[0], nodes[2], nodes[1]);
	set_children(nodes[1], NULL,	 NULL);
	set_children(nodes[2], nodes[3], nodes[4]);
	set_children(nodes[3], NULL,	 NULL);
	set_children(nodes[4], nodes[5], NULL);
	set_children(nodes[5], NULL,	 NULL);

	return build_tree("Binary Tree 2",
			  "        ┌────── 0 ──────┐\n"
			  "┌────── 2 ──────┐       1\n"
			  "3       ┌────── 4\n"
			  "        5",
			  "6", "4", nodes[0]);
}

struct BTree *init_tree3(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6);

	set_children(nodes[0], nodes[1], nodes[2]);
	set_children(nodes[1], nodes[4], nodes[3]);
	set_children(nodes[2], NULL,	 NULL);
	set_children(nodes[3], nodes[5], NULL);
	set_children(nodes[4], NULL,	 NULL);
	set_children(nodes[5], NULL,	 NULL);

	return build_tree("Binary Tree 3",
			  "        ┌────── 0 ──────┐\n"
			  "┌────── 1 ──────┐       2\n"
			  "4       ┌────── 3\n"
			  "        5",
			  "6", "4", nodes[0]);
}

struct BTree *init_tree4(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6ul);

	set_children(nodes[0], nodes[2], nodes[1]);
	set_children(nodes[1], NULL,	 nodes[3]);
	set_children(nodes[2], nodes[4], NULL);
	set_children(nodes[3], NULL,	 nodes[5]);
	set_children(nodes[4], NULL,	 NULL);
	set_children(nodes[5], NULL,	 NULL);

	return build_tree("Binary Tree 4",
			  "        ┌────── 0 ──────┐\n"
			  "┌────── 2               1 ──────┐\n"
			  "4                               3 ──────┐\n"
			  "                                        5",
			  "6", "4", nodes[0]);
}

struct BTree *init_tree5(void)
{
	struct BTreeNode *nodes[5];

	init_nodes(&nodes[0], 5);

	set_children(nodes[0], nodes[1], nodes[2]);
	set_children(nodes[1], nodes[3], nodes[4]);
	set_children(nodes[2], NULL,	 NULL);
	set_children(nodes[3], NULL,	 NULL);
	set_children(nodes[4], NULL,	 NULL);

	return build_tree("Binary Tree 5",
			  "        ┌────── 0 ──────┐\n"
			  "┌────── 1 ──────┐       2\n"
			  "3               4",
			  5ul, 3ul, nodes[0]);
}

struct BTree *init_tree6(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6ul);

	set_children(nodes[0], nodes[2], nodes[1]);
	set_children(nodes[1], nodes[3], nodes[4]);
	set_children(nodes[2], NULL,	 NULL);
	set_children(nodes[3], NULL,	 NULL);
	set_children(nodes[4], nodes[5], NULL);
	set_children(nodes[5], NULL,	 NULL);

	return build_tree("Binary Tree 6",
			  "        ┌────── 0 ──────┐\n"
			  "        2       ┌────── 1 ──────┐\n"
			  "                3       ┌────── 4\n"
			  "                        5",
			  "6", "4", nodes[0]);
}

struct BTree *init_tree7(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6ul);

	set_children(nodes[0], nodes[2], nodes[1]);
	set_children(nodes[1], nodes[4], nodes[3]);
	set_children(nodes[2], NULL,	 NULL);
	set_children(nodes[3], NULL,	 NULL);
	set_children(nodes[4], NULL,	 nodes[5]);
	set_children(nodes[5], NULL,	 NULL);

	return build_tree("Binary Tree 7",
			  "        ┌────── 0 ──────┐\n"
			  "        2       ┌────── 1 ──────┐\n"
			  "                4 ──────┐       3\n"
			  "                        5",
			  "6", "4", nodes[0]);
}

inline struct BTree *build_tree(const char *name,
				const char *display,
				const char *count,
				const char *depth,
				struct BTreeNode *root)
{
	struct BTree *tree;

	HANDLE_MALLOC(tree,	     sizeof(struct BTree));
	HANDLE_MALLOC(tree->name,    sizeof(char) * 16ul);
	HANDLE_MALLOC(tree->display, sizeof(char) * 254ul);
	HANDLE_MALLOC(tree->count,   sizeof(char) * 4ul);
	HANDLE_MALLOC(tree->depth,   sizeof(char) * 4ul);

	strcpy(tree->name,    name);
	strcpy(tree->display, display);
	strcpy(tree->count,   count);
	strcpy(tree->depth,   depth);
	tree->root  = root;

	return tree;
}

inline void set_children(struct BTreeNode *parent,
			 struct BTreeNode *l_child,
			 struct BTreeNode *r_child)
{
	parent->l_child = l_child;
	parent->r_child = r_child;
}

inline void init_nodes(struct BTreeNode **nodes,
		       const size_t count)
{
	for (int i = 0; i < count; ++i) {
		HANDLE_MALLOC(nodes[i], sizeof(struct BTreeNode));
		nodes[i]->value = i;
	}
}

inline void free_tree(struct BTree *tree)
{
	free_nodes(tree->root);
	free(tree->depth);
	free(tree->count);
	free(tree->display);
	free(tree->name);
	free(tree);
}

inline void free_nodes(struct BTreeNode *root)
{
	if (root == NULL)
		return;

	free_nodes(root->l_child);
	free_nodes(root->r_child);
	free(root);
}
