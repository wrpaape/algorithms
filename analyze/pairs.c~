#include "utils/utils.h"
#include "utils/rand.h"
#include "pairs.h"

#define COUNT (1ul << 7)

inline int compare(double x,
		   double y)
{
	if (x < y) return -1;
	if (x > y) return  1;
	else	   return  0;
}
inline void swap_ij(double *array,
		    const ptrdiff_t i,
		    const ptrdiff_t j)
{
	const double tmp_swap = array[i];
	array[i] = array[j];
	array[j] = tmp_swap;
}

void run_pairs(void)
{
	double nuts[COUNT];
	double bolts[COUNT];

	init_nuts_and_bolts(&nuts[0l], &bolts[0l], COUNT);

	puts("shuffled:");
	print_nuts_and_bolts(&nuts[0l], &bolts[0l], COUNT);

	match_nuts_and_bolts(&nuts[0l], &bolts[0l], COUNT);
}

static inline void match_nuts_and_bolts(double *nuts,
					double *bolts,
					const size_t count)
{
}

inline void init_nuts_and_bolts(double *nuts,
				double *bolts,
				const size_t count)
{
	for (size_t i = 0ul; i < count; ++i)
		nuts[i] = rand_dbl_upto(500.0);

	memcpy(bolts, nuts, sizeof(double) * count);

	shuffle_array(bolts, count, sizeof(double));
}

inline void print_nuts_and_bolts(double *nuts,
				 double *bolts,
				 const size_t count)
{
	const size_t i_last = count - 1ul;
	size_t i;

	puts("nuts: {");

	for (i = 0; i < i_last; ++i)
		printf("%f, ", nuts[i]);

	printf("%f\n}\n\nbolts: {\n", nuts[i_last]);

	for (i = 0; i < i_last; ++i)
		printf("%f, ", bolts[i]);

	printf("%f\n}\n", bolts[i_last]);
}
