#include <utils/utils.h>


struct SuffixTree {
	struct SuffixNode **root_map;
	struct SuffixNode *nodes;
	size_t int_node_cnt;
	size_t ext_node_cnt;
	size_t tot_node_cnt;
};

struct SuffixNode {
	const char *rem_match;
	const char *suffix;
	struct SuffixNode **edge_map;
};



struct SuffixTree *build_suffix_tree(const char *string);

void do_insert_suffix_leaf(struct SuffixNode **const restrict edge_map,
			   struct SuffixNode **restrict internal,
			   struct SuffixNode *const restrict leaf,
			   const char *rem_string);
