#include "utils/utils.h"
#include "utils/rand.h"
#include "pairs.h"

#define COUNT (1ul << 7)

inline int compare_dbl_nodes(struct DblNode *node1,
			     struct DblNode *node2)
{
	const double dbl1 = node1->value;
	const double dbl2 = node2->value;

	if (dbl1 < dbl2) return -1;
	if (dbl1 > dbl2) return  1;
	else		 return  0;
}

inline void swap_dbl_nodes(struct DblNode *node1,
			   struct DblNode *node2)
{
	struct DblNode *tmp;

	tmp = node1->prev;
	node1->prev = node2->prev;
	node2->prev = tmp;

	tmp = node1->next;
	node1->next = node2->next;
	node2->next = tmp;
}

void run_pairs(void)
{
	struct DblNode nuts[COUNT];
	struct DblNode bolts[COUNT];

	init_nuts_and_bolts(&nuts[0l], &bolts[0l], COUNT);

	puts("shuffled:");
	print_nuts_and_bolts(&nuts[0l], &bolts[0l]);

	match_nuts_and_bolts(&nuts[0l], &bolts[0l], COUNT);
}

static inline void match_nuts_and_bolts(struct DblNode *nuts,
					struct DblNode *bolts,
					const size_t count)
{
}

void init_nuts_and_bolts(struct DblNode *nuts,
			 struct DblNode *bolts,
			 const size_t count)
{
	const size_t i_last = count - 1ul;
	double values[count];
	size_t i;
	struct DblNode *prev;

	for (i = 0ul; i < count; ++i)
		values[i] = rand_dbl_upto(500.0);

	i = 0ul;
	prev = NULL;

	while (1) {
		nuts[i].value = values[i];
		nuts[i].prev  = prev;

		if (i == i_last)
			break;

		prev = &nuts[i];
		++i;
		prev->next = &nuts[i];
	}

	nuts[i_last].next = NULL;


	shuffle_array(values, count, sizeof(double));


	i = 0ul;
	prev = NULL;

	while (1) {
		bolts[i].value = values[i];
		bolts[i].prev  = prev;

		if (i == i_last)
			break;

		prev = &bolts[i];
		++i;
		prev->next = &bolts[i];
	}

	bolts[i_last].next = NULL;
}

inline void print_nuts_and_bolts(struct DblNode *nuts,
				 struct DblNode *bolts)
{
	struct DblNode *node;

	puts("nuts: {");

	for (node = nuts; node->next != NULL; node = node->next)
		printf("%f, ", node->value);

	printf("%f\n}\n\nbolts: {\n", node->value);

	for (node = bolts; node->next != NULL; node = node->next)
		printf("%f, ", node->value);

	printf("%f\n}\n", node->value);
}
