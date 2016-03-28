#include "utils.h"
#include "maps/generator.h"
#include <time.h>

#define MAX_RAND (1u << 32)

int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost)
{

	int **grid;

	pcg32_random_t rng;
	pcg32_srandom_r(&rng, time(NULL), (intptr_t)&rng);

	int cost = rand_in_range(&rng, min_cost, max_cost);

	return NULL;
}

inline int rand_in_range(pcg32_random_t *rngptr,
			 const int lbound,
			 const int rbound)
{


	printf("rng: %u\n", (unsigned) pcg32_random_r(rngptr));

	return 0;
}

