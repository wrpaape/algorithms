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

	int ***grid = init_grad_grid(res_x, res_y);

	printf("grid[3][3][0]: %d\n", grid[3][3][0]);
	printf("grid[3][3][1]: %d\n", grid[3][3][1]);
	printf("grid[3][3][2]: %d\n", grid[3][3][2]);

	return NULL;
}

int ***init_grad_grid(const size_t res_x,
		      const size_t res_y)
{
	int ***grid;
	int **col;
	int *grad;
	int x, y, dir;

	const size_t SIZE_COL  = sizeof(int *) * res_y;
	const size_t SIZE_GRAD = sizeof(int)   * 3lu;


	HANDLE_MALLOC(grid, sizeof(int **) * res_x);

	for (x = 0; x < res_x; ++x) {

		HANDLE_MALLOC(col, SIZE_COL);

		for (y = 0; y < res_y; ++y) {

			HANDLE_MALLOC(grad, SIZE_GRAD);

			for (dir = 0; dir < 3; ++dir) {

				grad[dir] = coin_flip() ? 1 : -1;
			}

			col[y] = grad;
		}

		grid[x] = col;
	}

	return grid;
}
