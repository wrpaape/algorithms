#ifndef SORTS_SORTS_RADIX_H_
#define SORTS_SORTS_RADIX_H_
struct UIntNode {
	unsigned int val;
	char *str;
	struct UIntNode *nxt;
};

static inline void strcpy_adv_ptr(char **dbl_ptr, char *str);

void radix_sort(struct UIntNode **head_ptr, const int min_clz);

#endif /* ifndef SORTS_SORTS_RADIX_H_ */

