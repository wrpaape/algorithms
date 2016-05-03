#include <utils/utils.h>


struct SuffixTree {
	struct SuffixNode **root_map;
	struct SuffixNode *nodes;
	size_t int_node_cnt;
	size_t ext_node_cnt;
	size_t tot_node_cnt;
};

struct SuffixNode {
	const char *from;
	const char *base;
	struct SuffixNode **edge_map;
};



struct SuffixTree *build_suffix_tree(const char *string);

void insert_suffix(struct SuffixNode **const restrict root_map,
		   struct SuffixNode **restrict internal,
		   struct SuffixNode *const restrict leaf,
		   const char *suffix);
