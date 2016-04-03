#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

#define EXIT_ON_ERROR(format, ...)	\
do {					\
	fprintf(stderr,			\
		"ERROR:	" format "\n"	\
		"errno: %s\n"		\
		"file:  %s\n"		\
		"func:  %s\n"		\
		"line:  %d\n"		\
		##__VA_ARGS__,		\
		strerror(errno),	\
		__FILE__,		\
		__func__,		\
		__LINE__);		\
		exit(EXIT_FAILURE);	\
} while (0)

#define INT_BITS (sizeof(int) * CHAR_BIT)



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
	int clz;
	int val;
	int min_clz = INT_BITS;
	struct IntNode *num = num_list;

	while (1) {
		val = (int) strtol(argv[i], NULL, 10);
		clz = __builtin_clz(val);

		if (clz < min_clz)
			min_clz = clz;

		num->val = val;
		strcpy_adv_ptr(&r_buff_ptr, argv[i]);

		if (i < num_count) {
			strcpy_adv_ptr(&r_buff_ptr, " ,");
			num->nxt = num_list + i;
			num = num->nxt;
			++i;

		} else {
			strcpy_adv_ptr(&r_buff_ptr, "\n}");
			*r_buff_ptr = '\0';
			num->nxt = NULL;
			break;
		}
	}

	radix_sort(&num_list, min_clz);


	while (1) {
	}

	return 0;
}

void radix_sort(struct IntNode **head_ptr, const int min_clz)
{
	const int MAX_SHIFT = INT_BITS - min_clz;
}


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
