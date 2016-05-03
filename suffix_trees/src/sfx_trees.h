#include <utils/utils.h>

struct SfxNode {
	char *upto;
	size_t count;
	struct SfxEdge *edges[CHAR_MAX];
};

struct SfxEdge {
	char *from;
	char **upto_ptr;
	struct SfxNode *children;
};

struct ActiveSfxState {
	struct SfxNode *node;
	size_t length;
	size_t remainder;
};


char **pattern_find_all(char *const restrict string,
			char *const restrict pattern);


struct SfxNode *create_sfx_tree(char *string);

void append_next_sfx(struct SfxNode **active_node_ptr,
		     char *sfx);


static inline struct SfxNode *init_sfx_node(char *const upto);

static inline struct SfxEdge *init_sfx_edge(char **const upto_ptr);
