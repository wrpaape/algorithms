#include "utils/utils.h"
#include "utils/rand.h"
#include "pairs.h"

#define COUNT (1ul << 7)

void run_pairs(void)
{
	struct DblNode nuts[COUNT];
	struct DblNode blts[COUNT];

	struct DblNode *matched_nuts;
	struct DblNode *matched_blts;


	init_nuts_and_bolts(&nuts[0l], &blts[0l], COUNT);

	puts("shuffled:");
	print_nuts_and_bolts(&nuts[0l], &blts[0l]);

	match_nuts_and_bolts(&matched_nuts, &matched_blts,
			     &nuts[0l],	    &blts[0l],	   COUNT);

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
	/* don't have to NULL check bc sentinels */
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

inline void splice_dbl_node(struct DblNode *node,
			    struct DblNode *prev,
			    struct DblNode *next)
{
	node->prev = prev;
	node->next = next;

	/* don't have to NULL check bc sentinels */
	prev->next = node;
	next->prev = node;
}

void do_match(struct DblNode **matched_nuts,
	      struct DblNode **matched_blts,
	      struct DblNode *prev_nut,
	      struct DblNode *next_nut,
	      struct DblNode *prev_blt,
	      struct DblNode *next_blt);
{
	if (prev_nut == next_nut) {
		*matched_nuts = prev_nut;
		*matched_blts = prev_blt;
		return;
	}


	/* splice out working list with sentinels */
	struct DblNode head_nut = { .prev = prev_nut->prev, .next = prev_nut };
	struct DblNode last_nut = { .prev = next_nut, .next = next_nut->next };
	struct DblNode head_blt = { .prev = prev_blt->prev, .next = prev_blt };
	struct DblNode last_blt = { .prev = next_blt, .next = next_blt->next };

	struct DblNode *pivot_nut = prev_nut;

	struct DblNode *tmp_swap;
	struct DblNode *pivot_blt;
	int comp;


	/* find 'pivot_blt' that matches 'pivot_nut' */
	while (1) {
		while (1) {
			comp = compare_dbl_nodes(pivot_nut, *head_blt_ptr);

			if (comp == 1)
				break;

			if (comp == 0) {
				pivot_blt = prev_blt;
				prev_blt  = prev_blt->next;
				goto FOUND_PIVOT_BLT_FROM_PREV;
			}

			prev_blt = prev_blt->next;
		}

		while (1) {
			comp = compare_dbl_nodes(pivot_nut, next_blt);

			if (comp == -1)
				break;

			if (comp == 0) {
				pivot_blt = next_blt;
				next_blt  = next_blt->prev;
				goto FOUND_PIVOT_BLT_FROM_NEXT;
			}

			next_blt = next_blt->prev;
		}

		/* swap misplaced nodes to proper sides of pivot */
		swap_dbl_nodes(prev_blt, next_blt);

		/* advance end pointers toward center of list */
		tmp_swap = prev_blt->prev;
		prev_blt = next_blt->next;
		next_blt = tmp_swap;
	}


	while (1) {

FOUND_PIVOT_BLT_FROM_PREV:

		while (1) {
			if (prev_blt == next_blt) {
				remove_dbl_node(pivot_blt);

				splice_dbl_node(pivot_blt,
						prev_blt,
						prev_blt->next);

				goto PARTITION_NUTS;
			}

			if (compare_dbl_nodes(pivot_nut, prev_blt) == 1)
				break;

			prev_blt = prev_blt->next;
		}

FOUND_PIVOT_BLT_FROM_NEXT:

		while (1) {
			if (next_blt == prev_blt) {
				remove_dbl_node(pivot_blt);

				splice_dbl_node(pivot_blt,
						prev_blt->prev,
						prev_blt);

				goto PARTITION_NUTS;
			}

			if (compare_dbl_nodes(pivot_nut, next_blt) == -1)
				break;

			next_blt = next_blt->prev;
		}

		/* swap misplaced nodes to proper sides of pivot */
		swap_dbl_nodes(prev_blt, next_blt);

		/* advance end pointers toward center of list */
		tmp_swap = prev_blt->prev;
		prev_blt = next_blt->next;
		next_blt = tmp_swap;
	}


PARTITION_NUTS:

	while (1) {
		while (1) {
			if (prev_nut == next_nut) {
				remove_dbl_node(pivot_nut);

				splice_dbl_node(pivot_nut,
						prev_nut,
						prev_nut->next);

				goto DO_RECURSE;
			}

			if (compare_dbl_nodes(pivot_blt, prev_nut) == 1)
				break;

			prev_nut = prev_nut->next;
		}

		while (1) {
			if (next_nut == prev_nut) {
				remove_dbl_node(pivot_nut);

				splice_dbl_node(pivot_nut,
						prev_nut->prev,
						prev_nut);

				goto DO_RECURSE;
			}

			if (compare_dbl_nodes(pivot_blt, next_nut) == -1)
				break;

			next_nut = next_nut->prev;
		}

		/* swap misplaced nodes to proper sides of pivot */
		swap_dbl_nodes(prev_nut, next_nut);

		/* advance end pointers toward center of list */
		tmp_swap = prev_nut->prev;
		prev_nut = next_nut->next;
		next_nut = tmp_swap;
	}

DO_RECURSE:

	/* remove sentinels */
	next_nut = last_nut.prev; next_nut->next = last_nut.next;
	prev_nut = head_nut.prev; prev_nut->next = head_nut.next;
	next_blt = last_blt.prev; next_blt->next = last_blt.next;
	prev_blt = head_blt.prev; prev_blt->next = head_blt.next;

	/* match nodes to the right of pivot */
	do_match(&pivot_blt->next, &pivot_nut->next,
		 pivot_nut->next,  next_nut,
		 pivot_blt->next,  next_blt);

	/* match nodes to the left of pivot */
	do_match(matched_nuts, matched_blts,
		 prev_nut,     pivot_nut->prev,
		 prev_blt,     pivot_blt->prev);
}

inline void match_nuts_and_bolts(struct DblNode **restrict matched_nuts,
				 struct DblNode **restrict matched_blts,
				 struct DblNode *restrict nuts,
				 struct DblNode *restrict blts,
				 const size_t count);
{
	const size_t i_last = count - 1ul;

	do_match(matched_nuts, matched_blts,
		 &nuts[0l],    &nuts[i_last],
		 &blts[0l],    &blts[i_last]);
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
