#include "exercises.h"

#define GRINCH_N (1ul << 4)
#define HEAP_ALLOC (1ul << 5)

int main(void)
{
	init_rng();
	run_heap();

	return 0;
}

void do_insert_next(int *const nodes,
		    const int next,
		    const ptrdiff_t i_next)
{
	printf("next: %d, i_next: %zd\n", next, i_next);
	if (i_next == 1l) {
		nodes[1l] = next;
		return;
	}

	const ptrdiff_t i_prnt = i_next / 2l;
	const int prnt = nodes[i_prnt];

	if (next < prnt) {
		nodes[i_next] = prnt;
		do_insert_next(nodes, i_next, i_prnt);
	} else {
		nodes[i_next] = next;
	}
}

void do_shift_next(int *const nodes,
		    const int next,
		    const ptrdiff_t i_next,
		    const ptrdiff_t i_base)
{
	const ptrdiff_t i_lchild = i_next * 2l;

	if (i_lchild > i_base)
		goto PLACE_NEXT;

	const int lchild = nodes[i_lchild];


	if (lchild < next) {

		if (i_lchild == i_base) {
			nodes[i_next]   = lchild;
			nodes[i_lchild] = next;
			return;
		}

		const ptrdiff_t i_rchild = i_lchild + 1l;

		const int rchild = nodes[i_rchild];

		if (lchild < rchild) {
			nodes[i_next] = lchild;
			do_shift_next(nodes, next, i_lchild, i_base);
		} else {
			nodes[i_next] = rchild;
			do_shift_next(nodes, next, i_rchild, i_base);
		}
		return;
	}

	if (i_lchild == i_base)
		goto PLACE_NEXT;

	const ptrdiff_t i_rchild = i_lchild + 1l;
	const int rchild = nodes[i_rchild];

	if (rchild < next) {
		nodes[i_next] = rchild;
		do_shift_next(nodes, next, i_rchild, i_base);
	}

PLACE_NEXT:
	nodes[i_next] = next;
}

inline int heap_extract(struct IntHeap *heap)
{
	int *const nodes = heap->nodes;
	const int root = nodes[1l];

	const int base = nodes[heap->count];

	--(heap->count);

	do_shift_next(nodes, base, 1l, heap->count);

	return root;
}

inline void heap_insert(struct IntHeap *heap,
			const int next)
{
	++(heap->count);
	do_insert_next(heap->nodes, next, heap->count);
}


void run_heap(void)
{
	ptrdiff_t i;
	struct IntHeap *heap = init_heap(HEAP_ALLOC);

	for (i = 0l; i < HEAP_ALLOC; ++i)
		heap_insert(heap, (int) rand_uint_upto(100u));

	PRINT_ARRAY((heap->nodes + 1l), heap->count, "%d");

	for (i = 0l; i < HEAP_ALLOC; ++i)
		printf("%d\n", heap_extract(heap));
}


inline struct IntHeap *init_heap(const size_t alloc)
{
	struct IntHeap *heap;
	int *nodes;
	HANDLE_MALLOC(heap,  sizeof(struct IntHeap));
	HANDLE_MALLOC(nodes, sizeof(int) * alloc);
	heap->nodes = &nodes[-1l];
	heap->count = 0ul;
	return heap;
}


struct BitVector *init_rand_bit_vector(const size_t size,
				       const int min,
				       const int max)
{
	const int span = max - min;
	if (size > span)
		return NULL;

	int *bits;
	struct BitVector *set;
	HANDLE_MALLOC(set, sizeof(struct BitVector));
	HANDLE_CALLOC(bits, size, (size_t) span);


	return set;
}

void run_set_union(void)
{
	struct BitVector *set1 = init_rand_bit_vector(50, -150, 150);
	struct BitVector *set2 = init_rand_bit_vector(10, -150, 150);

}

ptrdiff_t split_data(int *data,
		     ptrdiff_t from,
		     ptrdiff_t upto)
{
	const ptrdiff_t i_pivot = from;
	const int pivot = data[i_pivot];

	while (1) {
		while (1) {
			++from;

			if (from == upto) {
				if (data[from] > pivot)
					--from;

				goto PLACE_PIVOT;
			}

			if (data[from] > pivot)
				break;
		}

		while (1) {
			if (data[upto] < pivot)
				break;

			--upto;

			if (upto == from) {
				--from;
				goto PLACE_PIVOT;
			}
		}

		EL_SWAP(data, from, upto);
	}

PLACE_PIVOT:
	EL_SWAP(data, i_pivot, from);
	return from;
}

inline void do_sort(int *data,
		    const ptrdiff_t from,
		    const ptrdiff_t upto)
{
	if (from < upto) {
		const ptrdiff_t split = split_data(data, from, upto);
		do_sort(data, from, split - 1);
		do_sort(data, split + 1, upto);
	}
}


void run_grinch(void)
{
	int players[GRINCH_N];
	ptrdiff_t i;
	const ptrdiff_t split = GRINCH_N / 2l;

	for (i = 0; i < GRINCH_N; ++i)
		players[i] = (int) rand_uint_upto(500u);

	do_sort(players, 0l, GRINCH_N - 1l);

	int good_avg = 0;
	int bad_avg  = 0;

	do {
		--i;
		good_avg += players[i];
	} while (i > split);

	do {
		--i;
		bad_avg += players[i];
	} while (i >= 0l);

	for (i = 0; i < GRINCH_N; ++i)
		printf("players[%zd]: %d\n", i, players[i]);

	printf("good: %ld\nbad:  %ld\ntot:  %ld\n",
	       good_avg / split, bad_avg / split,
	       (good_avg + bad_avg) / GRINCH_N);
}
