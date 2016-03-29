#include "utils/utils.h"
#include "utils/rand.h"
#include "maps/generator.h"


int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost)
{

	/* int **grid; */
	init_rng();

	/* double ***grad_grid = init_grad_grid(res_x, res_y); */

	printf("rand: %f\n", rand_in_dub_range(-1.0, 1.0));

	return NULL;
}



double ***init_grad_grid(const size_t res_x,
			 const size_t res_y)
{
	double ***grad_grid;
	double **col;
	double *grad;
	int x, y, dir;

	const size_t SIZE_COL  = sizeof(double *) * res_y;
	const size_t SIZE_GRAD = sizeof(double)   * 3lu;


	HANDLE_MALLOC(grad_grid, sizeof(double **) * res_x);

	for (x = 0; x < res_x; ++x) {

		HANDLE_MALLOC(col, SIZE_COL);

		for (y = 0; y < res_y; ++y) {

			HANDLE_MALLOC(grad, SIZE_GRAD);

			for (dir = 0; dir < 3; ++dir) {

				grad[dir] = coin_flip() ? 1 : -1;
			}

			col[y] = grad;
		}

		grad_grid[x] = col;
	}

	return grad_grid;
}
