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

inline struct DblNode **enqueue_dbl_node(struct DblNode **qend,
					 struct DblNode *node)
{
	node->prev = *qend;
	*qend = node;
	return &node->next;
}




void do_match(struct DblNode *nut_head,
	      struct DblNode *nut_end,
	      struct DblNode *blt_head,
	      struct DblNode *blt_end)
{
	struct DblNode *sml_nut_head = NULL;
	struct DblNode *lrg_nut_head = NULL;
	struct DblNode *sml_blt_head = NULL;
	struct DblNode *lrg_blt_head = NULL;

	struct DblNode **sml_nut_end = &sml_nut_head;
	struct DblNode **lrg_nut_end = &lrg_nut_head;
	struct DblNode **sml_blt_end = &sml_blt_head;
	struct DblNode **lrg_blt_end = &lrg_blt_head;


	struct DblNode *blt_pivot;

	struct DblNode *nut_pivot = nut_head;
	nut_head = nut_head->next;

	/* find 'blt_pivot', splitting blts into "smaller" and "larger" lists
	 * while traversing */

	while (1) {
		switch (compare_dbl_nodes(nut_pivot, blt_head)) {
		case -1:
			sml_blt_end = enqueue_dbl_node(sml_blt_end, blt_head);
			break;
		case  1:
			lrg_blt_end = enqueue_dbl_node(lrg_blt_end, blt_head);
			break;
		default:
			blt_pivot = blt_head;
			goto SPLIT_REMAINING_BOLTS;
		}
		blt_head = blt_head->next;
	}

SPLIT_REMAINING_BOLTS:
	for (blt_head  = blt_head->next;
	     blt_head != blt_end;
	     blt_head  = blt_head->next) {

		if (compare_dbl_nodes(nut_pivot, blt_head) < 0)
			sml_blt_end = enqueue_dbl_node(sml_blt_end, blt_head);
		else
			lrg_blt_end = enqueue_dbl_node(lrg_blt_end, blt_head);
	}


	while (1) {
		switch (compare_dbl_nodes(blt_pivot, nut_head)) {
		case -1:
			sml_nut_end = enqueue_dbl_node(sml_nut_end, nut_head);
			break;
		case  1:
			lrg_nut_end = enqueue_dbl_node(lrg_nut_end, nut_head);
			break;
		default:
			nut_pivot = nut_head;
			goto SPLIT_REMAINING_NUTS;
		}
		nut_head = nut_head->next;
	}

SPLIT_REMAINING_NUTS:
	for (nut_head  = nut_head->next;
	     nut_head != blt_end;
	     nut_head  = nut_head->next) {

		if (compare_dbl_nodes(blt_pivot, nut_head) < 0)
			sml_nut_end = enqueue_dbl_node(sml_nut_end, nut_head);
		else
			lrg_nut_end = enqueue_dbl_node(lrg_nut_end, nut_head);
	}

}

static inline void match_nuts_and_bolts(struct DblNode *nuts,
					struct DblNode *bolts)
{
	do_match(&nuts[0l],
		 NULL,
		 &bolts[0l],
		 NULL);
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
