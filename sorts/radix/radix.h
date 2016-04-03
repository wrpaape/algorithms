#ifndef SORTS_SORTS_RADIX_H_
#define SORTS_SORTS_RADIX_H_
struct IntNode {
	int val;
	char *str;
	struct IntNode *nxt;
};

static inline void strcpy_adv_ptr(char **dbl_ptr, char *str);

void radix_sort(struct IntNode **head_ptr, const int min_clz);

#endif /* ifndef SORTS_SORTS_RADIX_H_ */

