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

struct SuffixBuildState {
	struct SuffixNode *act_node;
	struct SuffixEdge *act_edge;
	size_t act_length;
	size_t rem_suffixes;
};


char **pattern_find_all(char *const restrict string,
			char *const restrict pattern);


struct SuffixNode *create_suffix_tree(char *restrict string);

void append_suffix(struct SuffixBuildState *state,
		   char *const string);

static inline struct SuffixNode *init_suffix_node(char *const restrict upto);

static inline struct SuffixEdge *init_suffix_edge(char **const restrict upto);
