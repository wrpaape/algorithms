#include "exercises.h"

#define GRINCH_N (1ul << 4)

 void node_to_string(char *buffer,
		     const void *node)
{
	sprintf(buffer, "%d", (int) node);
}



int compare(const void *x,
	    const void *y)
{
	return ((int) x) < ((int) y);
}

int main(void)
{
	init_rng();
	/* run_grinch(); */
	/* run_set_union(); */

	int array[10];
	ptrdiff_t i;

	for (i = 0; i < 10; ++i)
		array[i] = (int) rand_uint_upto(500u);

	for (i = 0; i < 10; ++i)
		printf("%d\n", array[i]);

	bheap_sort((void **) &array[0ul], 10ul, &compare);

	for (i = 0; i < 10; ++i)
		printf("  %d\n", array[i]);

	return 0;
}


struct BitVector *init_rand_bit_vector(const size_t size,
				       const int min,
				       const int max)
{
	const int span = max - min;
	if (size > span)
		return NULL;

	/* const size_t alloc = next_pow_two(span); */

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

inline void swap_ij(int *data,
		    const ptrdiff_t i,
		    const ptrdiff_t j)
{
	const int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
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

		swap_ij(data, from, upto);
	}

PLACE_PIVOT:
	swap_ij(data, i_pivot, from);
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
