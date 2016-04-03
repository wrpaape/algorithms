#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <gmp.h>
#define NDEBUG

#define EXIT_ON_ERROR(format, ...)	\
do {					\
	fprintf(stderr,			\
		"ERROR:	" format "\n"	\
		"errno: %s\n",		\
		##__VA_ARGS__,		\
		strerror(errno));	\
exit(1);				\
} while (0)

#define INT_BITS (sizeof(int) * CHAR_BIT)

static inline void strcpy_adv_ptr(char **dbl_ptr, char *str);

inline void strcpy_adv_ptr(char **dbl_ptr, char *str)
{
	char *ptr = *dbl_ptr;

	int i = 0;

	while (str[i] != '\0') {
		ptr[i] = str[i];
		++i;
	}

	*dbl_ptr = ptr + i;
}

struct IntNode {
	int val;
	struct IntNode *nxt;
};

int main(int argc, char *argv[]) {

	if (argc < 2)
		EXIT_ON_ERROR("pls provide at least 1 integer to be sorted");

	const size_t num_count = argc - 1lu;
	/* abs(INT_MIN) > abs(INT_MAX) in 2’s compliment architectures */

	const size_t MAX_DEC_DIGITS = ((size_t) floor(log10(-((double) INT_MIN)))) + 1lu;

	const size_t SAFE_BUFF_SIZE = sizeof("sorted: {\n\t\n}")	   /* larger of labels + null byte */
				    + ((MAX_DEC_DIGITS + 1lu) * num_count) /* for ASCII dec chars + sign char */
				    + (2lu * (num_count - 1lu));           /* for pad chars  ", " */

	char *raw_buff	  = malloc(sizeof(char) * SAFE_BUFF_SIZE);
	char *sorted_buff = malloc(sizeof(char) * SAFE_BUFF_SIZE);

	char *r_buff_ptr = raw_buff;
	char *s_buff_ptr = sorted_buff;

	/* set buffer labels */
	strcpy_adv_ptr(&r_buff_ptr, "raw:    {\n\t");
	strcpy_adv_ptr(&s_buff_ptr, "sorted: {\n\t");


	/* convert ‘argv’ to list of integers ‘num_list’ and init buckets */
	struct IntNode *num_list = malloc(sizeof(struct IntNode) * num_count);


	/* ignoring program name */
	int i = 1;
	struct IntNode *num = num_list;
	struct IntNode *next_num = NULL;

	while (1) {
		num->nxt = next_num;
		num->val = (int) strtol(argv[i], NULL, 10);
		strcpy_adv_ptr(&r_buff_ptr, argv[i]);

		if (i < num_count) {
			strcpy_adv_ptr(&r_buff_ptr, " ,");
			next_num = num;
			num	 = num_list + i;
			++i;

		} else {
			strcpy_adv_ptr(&r_buff_ptr, "\n}");
			*r_buff_ptr = '\0';
			break;
		}
	}

	/* begin sorting */
	struct IntNode *small_bucket;
	struct IntNode *large_bucket;
	struct IntNode **link;


	int bit = 1;
	size_t shift = 1lu;

	while (1) {

		large_bucket = NULL;

		while (num->val & bit) {

			num->nxt = large_bucket;
			large_bucket = num;


			if (next_num == NULL) {
				num = large_bucket;
				goto NEXT_BUCKETS;
			}

			num = next_num;
			next_num = next_num->nxt;
		}


		link = &(num->nxt);
		small_bucket = num;

		while (next_num != NULL) {
			printf("num->val: %d\n", num->val);
			num = next_num;

			if (num->val & bit) {
				num->nxt = large_bucket;
				large_bucket = num;
			} else {
				num->nxt = small_bucket;
				small_bucket = num;
			}

			next_num = next_num->nxt;
		}

		/* concat buckets */
		*link = large_bucket;

		/* reset num */
		num = small_bucket;

NEXT_BUCKETS:
		if (shift == INT_BITS)
			break;

		bit = 1 << shift;
		++shift;
		next_num = num->nxt;
	}


	do {
		printf("%d\n", num->val);
		num = num->nxt;
	} while (num != NULL);


	return 0;
}
