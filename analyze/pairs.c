#include "utils/utils.h"
#include "utils/rand.h"
#include "pairs.h"

#define COUNT (1ul << 7)

void run_pairs(void)
{
	struct DblNode nuts[COUNT];
	struct DblNode blts[COUNT];


	init_nuts_and_bolts(&nuts[0l], &blts[0l], COUNT);

	puts("shuffled:");
	print_nuts_and_bolts(&nuts[0l], &blts[0l]);

	match_nuts_and_bolts(&nuts[0l], &blts[0l], COUNT);

	puts("matched:");
	print_nuts_and_bolts(&nuts[0l], &blts[0l]);
}

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
	struct DblNode *tmp_swap;

	tmp_swap = node1->prev;
	node1->prev = node2->prev;
	node2->prev = tmp_swap;

	tmp_swap = node1->next;
	node1->next = node2->next;
	node2->next = tmp_swap;
}

inline void remove_dbl_node(struct DblNode *node)
{
	struct DblNode *prev = node->prev;
	struct DblNode *next = node->next;

	if (prev == NULL) {
		if (next != NULL)
			next->prev = NULL;
		return;
	}

	if (next == NULL) {
		prev->next = NULL;
		return;
	}

	prev->next = next;
	next->prev = prev;
}

void do_match(struct DblNode *head_nut,
	      struct DblNode *last_nut,
	      struct DblNode *head_blt,
	      struct DblNode *last_blt)
{
	if (head_nut == last_nut)
		return;

	struct DblNode *tmp_swap;
	struct DblNode *pivot_blt;

	struct DblNode *pivot_nut = head_nut;

	int comp;


	/* find 'pivot_blt' that matches 'pivot_nut' */
	while (1) {
		while (1) {
			comp = compare_dbl_nodes(pivot_nut, head_blt);

			if (comp == 1)
				break;

			if (comp == 0) {
				pivot_blt = head_blt;
				goto FOUND_PIVOT_BLT_FROM_HEAD;
			}

			head_blt = head_blt->next;
		}

		while (1) {
			comp = compare_dbl_nodes(pivot_nut, last_blt);

			if (comp == -1)
				break;

			if (comp == 0) {
				pivot_blt = last_blt;
				goto FOUND_PIVOT_BLT_FROM_LAST;
			}

			last_blt = last_blt->prev;
		}

		/* swap misplaced nodes to proper sides of pivot */
		swap_dbl_nodes(head_blt, last_blt);

		/* advance end pointers toward center of list */
		tmp_swap = head_blt->prev;
		head_blt = last_blt->next;
		last_blt = tmp_swap;
	}


	while (1) {

FOUND_PIVOT_BLT_FROM_HEAD:

		while (1) {
			head_blt = head_blt->next;

			if (head_blt == last_blt)
				remove_dbl_node(pivot_blt);
				goto PARTITION_NUTS;

			if (compare_dbl_nodes(pivot_nut, head_blt) == 1)
				break;
		}

FOUND_PIVOT_BLT_FROM_LAST:

		while (1) {
			last_blt = last_blt->prev;

			if (last_blt == head_blt) {

				remove_dbl_node(pivot_blt);

				goto PARTITION_NUTS;
			}

			if (compare_dbl_nodes(pivot_nut, last_blt) == -1)
				break;
		}

		/* swap misplaced nodes to proper sides of pivot */
		swap_dbl_nodes(head_blt, last_blt);

		/* advance end pointers toward center of list */
		tmp_swap = head_blt->prev;
		head_blt = last_blt->next;
		last_blt = tmp_swap;
	}


PARTITION_NUTS:

	pivot_blt


}

inline void match_nuts_and_bolts(struct DblNode *restrict nuts,
				 struct DblNode *restrict blts,
				 const size_t count);
{
	const size_t i_last = count - 1ul;

	do_match(&nuts[0l],
		 &nuts[i_last],
		 &blts[0l],
		 &blts[i_last]);
}

void init_nuts_and_bolts(struct DblNode *nuts,
			 struct DblNode *blts,
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
		blts[i].value = values[i];
		blts[i].prev  = prev;

		if (i == i_last)
			break;

		prev = &blts[i];
		++i;
		prev->next = &blts[i];
	}
	blts[i_last].next = NULL;
}

void print_nuts_and_bolts(struct DblNode *nuts,
			  struct DblNode *blts)
{
	puts("nuts: {");

	while (1) {
		printf("%f, ", nuts->value);
		if (nuts->next == NULL)
			break;
		nuts = nuts->next;
	}

	printf("%f\n}\n\nbolts: {\n", nuts->value);

	while (1) {
		printf("%f, ", blts->value);

		if (blts->next == NULL)
			break;

		blts = blts->next;
	}

	printf("%f\n}\n", blts->value);
}
