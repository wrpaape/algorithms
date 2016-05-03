#include <utils/utils.h>


struct SuffixTree {
	struct SuffixSubstring **root;
	size_t edge_count;
	size_t leaf_count;
	size_t node_count;
};

struct SuffixSubstring {
	char *from;
	char *base;
	struct SuffixSubstring **next;
};


struct SuffixTree *build_suffix_tree(char *string);
