#include "utils/utils.h"
#include "utils/rand.h"
#include "maps/generator.h"

int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost)
{

	int **grid;

	init_rng();

	printf("rand: %d\n", rand_in_range(0, 9));

	return NULL;
}
