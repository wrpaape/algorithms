#ifndef ANALYZE_TREE_COMPARE_H_
#define ANALYZE_TREE_COMPARE_H_
struct BTreeNode {
	int value;
	struct BTreeNode *l_child;
	struct BTreeNode *r_child;
};

struct BTree {
	char *name;
	char *display;
	struct BTreeNode *root;
};

void run_tree_compare(void);

static inline void compare_trees(struct BTree *tree1,
				 struct BTree *tree2);

bool similar_binary_trees(struct BTreeNode *node1,
			  struct BTreeNode *node2);

struct BTree *init_tree1(void);
struct BTree *init_tree2(void);
struct BTree *init_tree3(void);
struct BTree *init_tree4(void);
struct BTree *init_tree5(void);

static inline struct BTree *build_tree(const char *name,
				       const char *display,
				       struct BTreeNode *root);

static inline void init_nodes(struct BTreeNode **nodes,
			      const size_t count);

static inline void set_children(struct BTreeNode *parent,
				struct BTreeNode *l_child,
				struct BTreeNode *r_child);

static inline void free_tree(struct BTree *tree);
static inline void free_nodes(struct BTreeNode *root);
#endif /* ifndef ANALYZE_TREE_COMPARE_H_ */
