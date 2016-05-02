#include <utils/utils.h>

struct SuffixNode {
	char *from;
	char *upto;
	struct SuffixNode *lateral;
	struct SuffixNode *next;
};


char **pattern_find_all(char *const restrict string,
			char *const restrict pattern);


/* inline void free_match(struct Match *match) */
/* { */
/* 	free(match->indices); */
/* 	free(match); */
/* } */
/* extern inline void free_match(struct Match *match); */
