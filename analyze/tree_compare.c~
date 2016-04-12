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

	compare_trees(tree1, tree2);
	compare_trees(tree1, tree3);
	compare_trees(tree1, tree4);
	compare_trees(tree1, tree5);

	free_tree(tree1);
	free_tree(tree2);
	free_tree(tree3);
	free_tree(tree4);
	free_tree(tree5);
}

inline void compare_trees(struct BTree *tree1,
			  struct BTree *tree2)
{
	printf("%s:\n%s\n\nis *%s*\n\n%s:\n%s\n\n",
	       tree1->name,
	       tree1->display,
	       similar_binary_trees(tree1->root, tree2->root)
	       ? "SIMILAR TO" : "DIFFERENT THAN",
	       tree2->name,
	       tree2->display);
}

bool similar_binary_trees(struct BTreeNode *node1,
			  struct BTreeNode *node2)
{
	if (node1 == NULL)
		return node2 == NULL;

	if (node2 == NULL)
		return node1 == NULL;

	if (node1->value != node2->value)
		return false;

	return (similar_binary_trees(node1->l_child, node2->l_child)  &&
		similar_binary_trees(node1->r_child, node2->r_child))
	    || (similar_binary_trees(node1->l_child, node2->r_child)  &&
		similar_binary_trees(node1->r_child, node2->l_child));
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
