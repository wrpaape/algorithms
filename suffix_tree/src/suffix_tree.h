#include <utils/utils.h>


struct SuffixTree {
	struct SuffixSubstring **root;
	size_t node_count;
	size_t leaf_count;
};

struct SuffixSubstring {
	char *from;
	char *base;
	struct SuffixSubstring **next;
};


struct SuffixSubstring *build_suffix_tree(char *string);
