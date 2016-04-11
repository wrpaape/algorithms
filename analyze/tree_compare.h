#ifndef ANALYZE_TREE_COMPARE_H_
#define ANALYZE_TREE_COMPARE_H_
struct BTreeNode {
	int value;
	struct BTreeNode *l_child;
	struct BTreeNode *r_child;
};

void run_tree_compare(void);

bool similar_binary_trees(struct BTreeNode *restrict node1,
			  struct BTreeNode *restrict node2);

struct BTreeNode *init_tree1(void);

static inline void free_tree(struct BTreeNode *root);
#endif /* ifndef ANALYZE_TREE_COMPARE_H_ */
