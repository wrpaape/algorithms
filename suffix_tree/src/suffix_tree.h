#include <utils/utils.h>


struct SuffixTree {
	struct SuffixNode **root_map;
	struct SuffixNode *nodes;
	size_t int_node_cnt;
	size_t ext_node_cnt;
	size_t tot_node_cnt;
};

struct SuffixNode {
	char *from;
	char *base;
	struct SuffixNode **edge_map;
};



struct SuffixTree *build_suffix_tree(char *string);
