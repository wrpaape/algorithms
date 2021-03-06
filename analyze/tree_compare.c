#include "utils/utils.h"
#include "utils/rand.h"
#include "tree_compare.h"

void run_tree_compare(void)
{
	struct BTreeNode *roots[8ul][1000ul];

	clock_t time_start;
	clock_t time_finish;
	clock_t time_elapsed;

	size_t i, j, h, n, nlgn;
	struct BTreeNode *root1;
	struct BTreeNode *root2;

	for (i = 0ul, h = 2ul; i < 8ul; ++i, h += 2ul) {

		for (j = 0ul; j < 1000ul; ++j) {
			roots[i][j] = init_tree(h);
		}

		time_start = clock();

		do {
			--j;
			root1 = roots[i][j];
			--j;
			root2 = roots[i][j];

			similar_trees(root1, root2);
		} while (j > 0ul);

		time_finish = clock();

		do {
			free_nodes(roots[i][j]);
			++j;

		} while (j < 1000ul);


		time_elapsed = time_finish - time_start;

		n = 1ul << h;
		nlgn = h * n;

		printf("N:    %zu\n"
		       "lgN:  %zu\n"
		       "NlgN: %zu\n"
		       "time: %zu\n"
		       "N/T:  %f\n",
		       n, h, nlgn, time_elapsed,
		       (500.0 * (double) n) / ((double) time_elapsed));

	}
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
	inspect_compare_trees(tree1, tree2);
	inspect_compare_trees(tree1, tree3);
	inspect_compare_trees(tree1, tree4);
	inspect_compare_trees(tree1, tree5);
	inspect_compare_trees(tree1, tree6);
	inspect_compare_trees(tree1, tree7);

	free_tree(tree1);
	free_tree(tree2);
	free_tree(tree3);
	free_tree(tree4);
	free_tree(tree5);
	free_tree(tree6);
	free_tree(tree7);
}

struct BTreeNode *init_tree(size_t h)
{
	if (h == 0ul)
		return NULL;

	struct BTreeNode *node;

	HANDLE_MALLOC(node, sizeof(struct BTreeNode));

	/* node->value = rand_in_int_range(1, 2); */
	node->value = 0;

	--h;
	node->l_child = init_tree(h);
	node->r_child = init_tree(h);

	return node;
}


inline void inspect_compare_trees(struct BTree *tree1,
				  struct BTree *tree2)
{
	struct CostAcc costs = {
		.frames = 0,
		.comparisons = 0,
		.accesses = 0
	};

	printf("================================\n"
	       "%s (%s nodes and depth of %s):\n"
	       "%s\n\n"
	       "is **%s**\n\n"
	       "%s (%s nodes and depth of %s):\n"
	       "%s\n\n"
	       "OVERHEAD:\n"
	       "%d frames\n"
	       "%d comparisons\n"
	       "%d accesses\n"
	       "================================\n",
	       tree1->name,
	       tree1->count,
	       tree1->depth,
	       tree1->display,
	       inspect_similar_trees(tree1->root,
				     tree2->root,
				     &costs) ?
	       "SIMILAR TO" : "DIFFERENT THAN",
	       tree2->name,
	       tree2->count,
	       tree2->depth,
	       tree2->display,
	       costs.frames,
	       costs.comparisons,
	       costs.accesses);
}

bool inspect_similar_trees(struct BTreeNode *node1,
			   struct BTreeNode *node2,
			   struct CostAcc *costs)
{
	++costs->frames;
	costs->comparisons += 2;

	if (node1 == NULL)
		return node2 == NULL;

	if (node2 == NULL)
		return false;

	++costs->comparisons;
	costs->accesses += 2;

	if (node1->value != node2->value)
		return false;

	costs->accesses += 4;

	if (inspect_similar_trees(node1->l_child, node2->l_child, costs) &&
	    inspect_similar_trees(node1->r_child, node2->r_child, costs))
		return true;

	costs->accesses += 4;

	return (inspect_similar_trees(node1->l_child, node2->r_child, costs) &&
		inspect_similar_trees(node1->r_child, node2->l_child, costs));
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
 *		 = O(1)
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
 *		 = O(1) + O(1)
 *		 = O(1)
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
 *		 = 3O(1) + O(1)
 *		 = O(1)
 *		 = RA
 *
 *
 *
 *
 *
 *
 * RECURSIVE CASE B:
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
 *		- node1->l_child is similar to node2->l_child
 *		- node1->r_child is similar to node2->r_child
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
 *		RB	(15) RECURSIVE CASE B
 *		C₃	(16) deference node1 pointer
 *		C₄	(17) access node1 field 'r_child'
 *		C₃	(18) deference node2 pointer
 *		C₄	(19) access node2 field 'r_child'
 *		RB	(20) RECURSIVE CASE B
 *		C₅	(21) return control to previous stack frame
 *
 *	ΣC_nodes = 2C₀ + C₁ + 3C₂ + 6C₃ + 6C₄ + C₅ + ΣC_children
 *		 = TA  + C₂ + 6C₃ + 6C₄
 *		 + (count(left  subtree nodes) - count(left  subtree leaves)) * RB
 *		 + (count(right subtree nodes) - count(right subtree leaves)) * RB
 *		 + count(left  subtree leaves) * RA
 *		 + count(right subtree leaves) * RA
 *		 + 2 * (count(left  sub-subtree nodes) - count(left  sub-subtree leaves)) * RB
 *		 + 2 * (count(right sub-subtree nodes) - count(right sub-subtree leaves)) * RB
 *		 + 2 * count(left  sub-subtree leaves) * RA
 *		 + 2 * count(right sub-subtree leaves) * RA
 *		 + ...
 *
 *		 = CONSTANT
 *		 + RB * (n / 2 - count(left  subtree leaves))
 *		 + RB * (n / 2 - count(right subtree leaves))
 *		 + RA * (count(left  subtree leaves))
 *		 + RA * (count(right subtree leaves))
 *		 + ...
 *
 *		 assuming perfect trees (hypothetical worst case)...
 *
 *		   count(left  subtree leaves)
 *		 = count(right subtree leaves)
 *		 = ((n / 2) + 1) / 2
 *		 = (n + 2) / 4
 *
 *		   count(left  sub-subtree leaves)
 *		 = count(right sub-subtree leaves)
 *		 = ((n / 4) + 1) / 2
 *		 = (n + 4) / 8
 *
 *   => ΣC_nodes = CONSTANT
 *		 + 2 * RB * ((n / 2) - ((n + 2) / 4))
 *		 + 2 * RA * ((n + 2) / 4)
 *		 + 4 * RB * ((n / 4) - ((n + 4) / 8))
 *		 + 4 * RA * ((n + 4) / 8)
 *		 + ...
 *
 *		 = CONSTANT
 *	num	 + RB * n + (RB - RA) * ((n + 2) / 2)
 *	tree	 + RB * n + (RB - RA) * ((n + 4) / 2)
 *	levels	 + RB * n + (RB - RA) * ((n + 8) / 2)
 *	 	 + ...
 *		 = O(nlog₂n)
 *
 *
 *
 * RECURSIVE CASE D (worst/most expensive):
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
 *
 *		RC	(15) RECURSIVE CASE C
 *
 *		C₃	(16) deference node1 pointer
 *		C₄	(17) access node1 field 'r_child'
 *		C₃	(18) deference node2 pointer
 *		C₄	(19) access node2 field 'r_child'
 *
 *		RB	(20) RECURSIVE CASE B
 *
 *		C₃	(21) deference node1 pointer
 *		C₄	(22) access node1 field 'l_child'
 *		C₃	(23) deference node2 pointer
 *		C₄	(24) access node2 field 'r_child'
 *
 *		RC	(25) RECURSIVE CASE C
 *
 *		C₃	(26) deference node1 pointer
 *		C₄	(27) access node1 field 'r_child'
 *		C₃	(28) deference node2 pointer
 *		C₄	(29) access node2 field 'l_child'
 *
 *		RB	(30) RECURSIVE CASE B
 *
 *		C₅	(31) return control to previous stack frame
 *
 *	ΣC_nodes = 2C₀ + C₁ + 3C₂ + 10C₃ + 10C₄ + C₅ + ΣC₍₁₅₎ + ΣC₍₂₀₎ + ΣC₍₂₅₎ + ΣC₍₃₀₎
 *		 = O(2nlog₂n) (twice RECURSIVE CASE C)
 *
 *
 *
 * CONDITIONS FOR GREATEST OVERHEAD (HYPOTHESIS):
 *
 *	- comparing perfect trees (all levels full) that are symmetric
 *	  and identical excluding the farthest right node of the bottom
 *	  level of node1
 *
 * ie:
 *		   node1				      node2
 *         ┌──────── 0 ────────┐           │          ┌──────── 0 ────────┐
 *    ┌─── 1 ───┐         ┌─── 1 ───┐      │     ┌─── 1 ───┐         ┌─── 1 ───┐
 * ┌─ 2 ─┐   ┌─ 2 ─┐   ┌─ 2 ─┐   ┌─ 2 ─┐   │  ┌─ 2 ─┐   ┌─ 2 ─┐   ┌─ 2 ─┐   ┌─ 2 ─┐
 * 3     3   3     3   3     3   3     4   │  3     3   3     3   3     3   3     3
 *
 * Comparing a pair of trees of this type will force the most expensive
 * case (RECURSIVE CASE D) at the top level and for all comparisons of right
 * subtrees.
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
	       similar_trees(tree1->root,
			     tree2->root) ?
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
			  "5", "3", nodes[0]);
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
