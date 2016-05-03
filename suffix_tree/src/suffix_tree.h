#include <utils/utils.h>

struct SuffixNode {
	char *base;
	size_t edge_count;
	struct SuffixNode *rem_suffix;
	struct SuffixNode *edges[CHAR_MAX];
};

struct SuffixNode *create_suffix_tree(char *string);

