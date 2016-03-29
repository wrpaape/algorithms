#include "utils/utils.h"
#include "utils/rand.h"
#include "maps/generator.h"
#include <math.h>

#define clamp(x, a, b) x < a ? a : (x > b ? b : x)

int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost)
{

	init_rng();

	double ***grad_grid = init_grad_grid(res_x + 1lu, res_y + 1lu);

	printf("grad_grid[0][0][0]: %f\n", grad_grid[0][0][0]);
	printf("grad_grid[0][0][1]: %f\n", grad_grid[0][0][1]);

	return NULL;
}

inline double linear_interp_step(const double lbound,
				 const double rbound,
				 const double weight)
{
	/* linearly interpolate between 'lbound' and 'rbound' according to
	 * 0.0 <= weight <= 1.0
	 **********************************************************************/
	return ((1.0 - weight) * lbound) + (weight * rbound);
}

inline double smoothstep(const double ledge,
			 const double redge,
			 const double x)
{
	const double step_weight = (x - ledge) / (redge - ledge);

	/* clamp 'step_weight' between '0.0' and '1.0'
	 **********************************************************************/
	if (step_weight < 0.0)
		return 0.0;

	if (step_weight > 1.0)
		return 1.0;

	return (step_weight * step_weight) * (3.0 - (2.0 * step_weight));
}



/* generates a 'vert_x × vert_y' matrix of random 2d unit vectors */
double ***init_grad_grid(const size_t verts_x,
			 const size_t verts_y)
{
	double ***grad_grid;
	double **col;
	double *grad;
	double u, v;
	int x, y;

	const size_t SIZE_COL  = sizeof(double *) * verts_y;
	const size_t SIZE_GRAD = sizeof(double)   * 2lu;


	HANDLE_MALLOC(grad_grid, sizeof(double **) * verts_x);

	for (x = 0; x < verts_x; ++x) {

		HANDLE_MALLOC(col, SIZE_COL);

		for (y = 0; y < verts_y; ++y) {

			HANDLE_MALLOC(grad, SIZE_GRAD);

			u = rand_in_dub_range(-1.0, 1.0);
			v = sqrt(1.0 - (u * u));

			grad[0] = u;
			grad[1] = coin_flip() ? v : -v;

			col[y] = grad;
		}

		grad_grid[x] = col;
	}

	return grad_grid;
}
