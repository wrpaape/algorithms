#include "utils/utils.h"
#include "utils/rand.h"
#include "pairs.h"

#define COUNT (1ul << 4)

#define PAUSE() usleep(100000)

#define PRINT_LABEL(LABEL)	\
do {				\
	puts(LABEL);		\
	fflush(stdout);		\
	PAUSE();			\
} while (0)


#define TRC(ADDRESS) ((unsigned char) ADDRESS)
#define INSPECT_DBL_NODE(N)						\
do {									\
	printf("\n****************************************"		\
	       "****************************************\n"		\
	       "%-25s | %-25s | %-25s\n"				\
	       "address: %-16d | %-25d | %-25d\n"			\
	       "prev:    %-16d | %-25d | %-25d\n"			\
	       "next:    %-16d | %-25d | %-25d\n"			\
	       "value:   %-16f | %-25f | %-25f\n\n",			\
	       #N,	     #N "->prev",	 #N "->next",		\
	       TRC(N),       TRC(N->prev),	 TRC(N->next),		\
	       TRC(N->prev), TRC(N->prev->prev), TRC(N->next->prev),	\
	       TRC(N->next), TRC(N->prev->next), TRC(N->next->next),	\
	       N->value,     N->prev->value,	 N->next->value);	\
	fflush(stdout);							\
} while (0)

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
	struct DblNode *swap1;
	struct DblNode *swap2;

	/* puts("=========================================" */
	/*      "========================================\n" */
	/*      "PRE SWAP:"); */
	/* INSPECT_DBL_NODE(node1); */
	/* INSPECT_DBL_NODE(node2); */
	/* don't have to NULL check bc sentinels */
	swap1 = node2->prev;
	swap2 = node1->prev;

	node1->prev = swap1;
	swap1->next = node1;
	node2->prev = swap2;
	swap2->next = node2;

	swap1 = node2->next;
	swap2 = node1->next;

	node1->next = swap1;
	swap1->prev = node1;
	node2->next = swap2;
	swap2->prev = node2;

	/* puts("\nPOST SWAP:"); */
	/* INSPECT_DBL_NODE(node1); */
	/* INSPECT_DBL_NODE(node2); */
	/* puts("========================================" */
	/*      "========================================="); */
	/* PAUSE(); */
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
	      struct DblNode *next_blt)
{
	if (prev_nut == next_nut) {
		PRINT_LABEL("\n	- TRIVIAL CASE - \n");
		*matched_nuts = prev_nut;
		*matched_blts = prev_blt;
		return;
	}

	assert(prev_nut != NULL);
	assert(next_nut != NULL);
	assert(next_blt != NULL);
	assert(next_blt != NULL);




	/* splice out working list with sentinels */
	PRINT_LABEL("splice out working list with sentinels");
	struct DblNode head_nut = { .value = -999.999, .prev = prev_nut->prev, .next = prev_nut };
	struct DblNode last_nut = { .value =  999.999, .prev = next_nut, .next = next_nut->next };
	struct DblNode head_blt = { .value = -999.999, .prev = prev_blt->prev, .next = prev_blt };
	struct DblNode last_blt = { .value =  999.999, .prev = next_blt, .next = next_blt->next };


	prev_nut->prev = &head_nut;
	next_nut->next = &last_nut;
	prev_blt->prev = &head_blt;
	next_blt->next = &last_blt;

	puts("nuts:");
	print_dbl_nodes(prev_nut, &last_nut);
	puts("bolts:");
	print_dbl_nodes(prev_blt, &last_blt);
	PAUSE();

	struct DblNode *pivot_nut = prev_nut;

	struct DblNode *tmp_swap;
	struct DblNode *pivot_blt;
	int comp;


	/* find 'pivot_blt' that matches 'pivot_nut' */
	PRINT_LABEL("find 'pivot_blt' that matches 'pivot_nut'");
	while (1) {
		while (1) {
			comp = compare_dbl_nodes(pivot_nut, prev_blt);

			if (comp == 1)
				break;

			if (comp == 0) {
				pivot_blt = prev_blt;
				prev_blt  = prev_blt->next;
				PRINT_LABEL("		FOUND_PIVOT_BLT_FROM_PREV");
				goto FOUND_PIVOT_BLT_FROM_PREV;
			}

			assert(prev_blt != NULL);

			prev_blt = prev_blt->next;
		}

		while (1) {
			comp = compare_dbl_nodes(pivot_nut, next_blt);

			if (comp == -1)
				break;

			if (comp == 0) {
				pivot_blt = next_blt;
				next_blt  = next_blt->prev;
				PRINT_LABEL("		FOUND_PIVOT_BLT_FROM_NEXT");
				goto FOUND_PIVOT_BLT_FROM_NEXT;
			}
			assert(next_blt != NULL);

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

				if (compare_dbl_nodes(pivot_nut, prev_blt) == 1) {
					splice_dbl_node(pivot_blt,
							prev_blt->prev,
							prev_blt);
				} else {
					splice_dbl_node(pivot_blt,
							prev_blt,
							prev_blt->next);
				}

				goto PARTITION_NUTS;
			}

			assert(prev_blt != NULL);

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
			assert(next_blt != NULL);

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
	PRINT_LABEL("PARTITION_NUTS");

	while (1) {
		while (1) {
			if (prev_nut == next_nut) {
				PRINT_LABEL("		NUTS PARTITIONED");
				remove_dbl_node(pivot_nut);

				if (compare_dbl_nodes(pivot_blt, prev_nut) == 1) {
					splice_dbl_node(pivot_nut,
							prev_nut->prev,
							prev_nut);
				} else {
					splice_dbl_node(pivot_nut,
							prev_nut,
							prev_nut->next);
				}

				goto DO_RECURSE;
			}

			if (compare_dbl_nodes(pivot_blt, prev_nut) == 1)
				break;

			prev_nut = prev_nut->next;
		}

		while (1) {
			if (next_nut == prev_nut) {
				PRINT_LABEL("		NUTS PARTITIONED");
				remove_dbl_node(pivot_nut);

				splice_dbl_node(pivot_nut,
						next_nut->prev,
						next_nut);

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

	INSPECT_DBL_NODE(pivot_nut);
	INSPECT_DBL_NODE(pivot_blt);

	/* remove sentinels, locating next pairs of head and tail nodes */
	PRINT_LABEL("remove sentinels, locating next pairs of head and tail nodes");
	next_nut       = last_nut.prev;
	next_nut->next = last_nut.next;
	if (last_nut.next != NULL)
		last_nut.next->prev = next_nut;

	prev_nut       = head_nut.next;
	prev_nut->prev = head_nut.prev;
	if (head_nut.prev != NULL)
		head_nut.prev->next = prev_nut;

	next_blt       = last_blt.prev;
	next_blt->next = last_blt.next;
	if (last_blt.next != NULL)
		last_blt.next->prev = next_blt;

	prev_blt       = head_blt.next;
	prev_blt->prev = head_blt.prev;
	if (head_blt.prev != NULL)
		head_blt.prev->next = prev_blt;

	/* match nodes to the right of pivot */
	PRINT_LABEL("DO RIGHT");
	do_match(&pivot_blt->next, &pivot_nut->next,
		 pivot_nut->next,  next_nut,
		 pivot_blt->next,  next_blt);

	/* match nodes to the left of pivot */
	PRINT_LABEL("DO LEFT");
	do_match(matched_nuts, matched_blts,
		 prev_nut,     pivot_nut->prev,
		 prev_blt,     pivot_blt->prev);
}

inline void match_nuts_and_bolts(struct DblNode **restrict matched_nuts,
				 struct DblNode **restrict matched_blts,
				 struct DblNode *restrict nuts,
				 struct DblNode *restrict blts,
				 const size_t count)
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

void print_dbl_nodes(struct DblNode *head_node,
		     struct DblNode *last_node)
{
	printf("{\n%f", head_node->value);
	while (1) {
		head_node = head_node->next;

		if (head_node == last_node)
			break;

		printf(", %f", head_node->value);
	}
	puts("\n}");
}

void print_nuts_and_bolts(struct DblNode *restrict nuts,
			  struct DblNode *restrict blts)
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
