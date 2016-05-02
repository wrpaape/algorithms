#include <utils/utils.h>

struct SuffixNode {
	char *upto;
	size_t count;
	struct SuffixEdge *edges[CHAR_MAX];
};

struct SuffixEdge {
	char *from;
	char **upto;
	struct SuffixNode *children;
};


char **pattern_find_all(char *const restrict string,
			char *const restrict pattern);


struct SuffixNode *create_suffix_tree(char *restrict string);

static inline struct SuffixNode *init_suffix_node(char *const restrict upto);

static inline struct SuffixEdge *init_suffix_edge(char **const restrict upto);
