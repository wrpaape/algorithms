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

/*
 * BEST/TRIVIAL CASE: node1 is NULL
 *
 *	C₀	(1)  copy local variable 'node1'
 *	C₀	(2)  copy local variable 'node2'
 *	C₁	(3)  call function
 *	C₂	(4)  compare node1 with NULL
 *	C₂	(5)  compare node2 with NULL
 *	C₄	(6)  return control to previous stack frame
 *
 *	overhead C|min = 2C₀ + C₁ + 2C₂ + C₄
 *
 * WORST CASE: compare balanced tree with completely mirrored counterpart
 *
 *	C₀	(1)  copy local variable 'node1'
 *	C₀	(2)  copy local variable 'node2'
 *	C₁	(3)  call function
 *	C₂	(4)  compare node1 with NULL
 *	C₂	(5)  compare node2 with NULL
 *	C₃	(6)  deference node1 for value
 *	C₃	(7)  deference node2 for value
 *	C₂	(8)  compare node1->value with node2->value
 *	C₃	(9)  deference node1 for l_child
 *	C₃	(10) deference node2 for l_child
 *		(11) repeat steps 1..5 for left children
 *	C₃	(12) deference node1 for r_child
 *	C₃	(13) deference node2 for r_child
 *		(14) repeat steps 1..5 for right children
 *	C₃	(15) deference node1 for l_child (ignore caching)
 *	C₃	(16) deference node2 for r_child (ignore caching)
 *		(17) repeat steps 1..5 for swapped children
 *	C₃	(18) deference node1 for r_child (ignore caching)
 *	C₃	(19) deference node2 for l_child (ignore caching)
 *		(20) repeat steps 1..5 for swapped children
 *	C₄	(21) return control to previous stack frame
 *
 *	overhead C|max = 2C₀ + C₁ + 3C₂ + 10C₃ + C₄
 *
 */
bool similar_binary_trees(struct BTreeNode *node1,
			  struct BTreeNode *node2)
{
	if (node1 == NULL)
		return node2 == NULL;

	if (node2 == NULL)
		return false;

	if (node1->value != node2->value)
		return false;

	return (similar_binary_trees(node1->l_child, node2->l_child)
	    &&  similar_binary_trees(node1->r_child, node2->r_child))
	    || (similar_binary_trees(node1->l_child, node2->r_child)
	    &&  similar_binary_trees(node1->r_child, node2->l_child));
}

inline void compare_trees(struct BTree *tree1,
			  struct BTree *tree2)
{
	printf("================================\n"
	       "%s:\n"
	       "%s\n\n"
	       "is **%s**\n\n"
	       "%s:\n"
	       "%s\n"
	       "================================\n",
	       tree1->name,
	       tree1->display,
	       similar_binary_trees(tree1->root, tree2->root)
	       ? "SIMILAR TO" : "DIFFERENT THAN",
	       tree2->name,
	       tree2->display);
}

struct BTree *init_tree1(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6);

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
			  nodes[0]);
}

struct BTree *init_tree2(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6);

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
			  nodes[0]);
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
			  nodes[0]);
}

struct BTree *init_tree4(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6);

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
			  nodes[0]);
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
			  nodes[0]);
}

struct BTree *init_tree6(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6);

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
			  nodes[0]);
}

struct BTree *init_tree7(void)
{
	struct BTreeNode *nodes[6];

	init_nodes(&nodes[0], 6);

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
			  nodes[0]);
}

inline struct BTree *build_tree(const char *name,
				const char *display,
				struct BTreeNode *root)
{
	struct BTree *tree;

	HANDLE_MALLOC(tree,	     sizeof(struct BTree));
	HANDLE_MALLOC(tree->name,    sizeof(char) * 254ul);
	HANDLE_MALLOC(tree->display, sizeof(char) * 254ul);

	strcpy(tree->name,    name);
	strcpy(tree->display, display);
	tree->root = root;

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
	free(tree->name);
	free(tree->display);
	free_nodes(tree->root);
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
