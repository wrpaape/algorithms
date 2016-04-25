#include <stdio.h>
#include <stdlib.h>
#include "exercises.h"

#define GRINCH_N (1ul << 4)


int main(void)
{
	run_grinch();
	return 0;
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

	init_rng();

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
