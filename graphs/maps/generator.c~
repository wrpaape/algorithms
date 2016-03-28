#include "utils.h"
#include "maps/generator.h"
#include <time.h>
#include <pcg_basic.h>


int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost)
{

	int **grid;

	srand(time(NULL));

	int cost = rand_in_range(min_cost, max_cost);

	return NULL;
}

inline int rand_in_range(const int lbound,
			 const int rbound)
{

	pcg32_random_t rng1, rng2, rng3;
	pcg32_srandom_r(&rng1, time(NULL), (intptr_t)&rng1);
	pcg32_srandom_r(&rng2, time(NULL), (intptr_t)&rng2);
	pcg32_srandom_r(&rng3, time(NULL), (intptr_t)&rng3);

	return rand_val;
}

