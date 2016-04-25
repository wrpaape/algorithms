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
	struct DblNode blts[COUNT];


	init_nuts_and_bolts(&nuts[0l], &blts[0l], COUNT);

	puts("shuffled:");
	print_nuts_and_bolts(&nuts[0l], &blts[0l]);

	match_nuts_and_bolts(&nuts[0l], &blts[0l], COUNT);

	puts("matched:");
	print_nuts_and_bolts(&nuts[0l], &blts[0l]);
}

inline struct DblNode **enqueue_dbl_node(struct DblNode **qend,
					 struct DblNode *node)
{
	node->prev = *qend;
	*qend = node;
	return &node->next;
}

void do_match(struct DblNode *head_nut,
	      struct DblNode *last_nut,
	      struct DblNode *head_blt,
	      struct DblNode *last_blt)
{
	if (head_nut == last_nut)
		return;

	struct DblNode *blt_pivot;

	struct DblNode *pivot_nut = head_nut;

	int comparison;


	/* find 'pivot_blt' that matches 'pivot_nut' */
	while (1) {

		while (1) {
			switch (compare_dbl_nodes(pivot_nut,
						  head_blt)) {
			case  1:
				goto FIND_BOLT_SWAP_PARTNER_PIVOT_UNKNOWN;

			case  0:
				blt_pivot = head_blt;
				goto SWAP_REMAINING_BOLTS;

			default:
				head_blt = head_blt->next;
			}
		}

FIND_BOLT_SWAP_PARTNER_PIVOT_UNKNOWN:

		while (1) {
			switch (compare_dbl_nodes(pivot_nut,
						  head_blt)) {
			case -1:
				goto FIND_BOLT_SWAP_PARTNER_PIVOT_UNKNOWN;

			case  0:
				blt_pivot = head_blt;
				goto SWAP_REMAINING_BOLTS;

			default:
				head_blt = head_blt->next;
			}
		}



	}

SWAP_REMAINING_BOLTS:
	while (1) {

		while (1) {
			switch (compare_dbl_nodes(pivot_nut,
						  head_blt)) {
			case 1:
				break;

			case 0:
				blt_pivot = head_blt;
				goto SWAP_REMAINING_BOLTS;
			default:
			}
		}

	}


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
