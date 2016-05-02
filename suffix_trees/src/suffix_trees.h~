#include <utils/utils.h>

struct SuffixNode {
	struct SuffixEdge *edges[CHAR_MAX];
	size_t count;
};

struct SuffixEdge {
	char *from;
	char **upto;
	struct SuffixNode *children;
};


char **pattern_find_all(char *const restrict string,
			char *const restrict pattern);


struct SuffixNode *create_suffix_tree(char *const restrict string);

/* inline void free_match(struct Match *match) */
/* { */
/* 	free(match->indices); */
/* 	free(match); */
/* } */
/* extern inline void free_match(struct Match *match); */

	/* /1* init alphabet *1/ */
	/* size_t char_counts[CHAR_MAX] = { [0 ... (CHAR_MAX - 1)] = 0ul }; */
	/* size_t uniq_chars = 0ul; */

	/* for (char *char_ptr = string; *char_ptr != '\0'; ++char_ptr) */
	/* 	++char_counts[*char_ptr]; */

	/* for (char key = CHAR_MAX; key >= '\0'; --key) { */
	/* 	if (char_counts[key] > 0ul) */
	/* 		++uniq_chars; */
	/* } */
