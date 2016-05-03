#include <utils/utils.h>


struct SuffixTree {
	struct SuffixSubstring **root_map;
	struct SuffixSubstring *node_buff;
	size_t int_node_cnt;
	size_t ext_node_cnt;
	size_t tot_node_cnt;
};

struct SuffixSubstring {
	char *from;
	char *base;
	struct SuffixSubstring **edge_map;
};


struct SuffixTree *build_suffix_tree(char *string);
