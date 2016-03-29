#include "utils/utils.h"
#include "utils/rand.h"
#include "maps/generator.h"
#include <math.h>

int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost)
{
	int **cost_grid;
	int *cost_col;
	double ***grad_grid;
	size_t x, y;

	init_rng();

	grad_grid = init_grad_grid(res_x + 1lu, res_y + 1lu);


	const size_t SIZE_COL  = sizeof(int)   * res_x;

	HANDLE_MALLOC(cost_grid, sizeof(int *) * res_y);

	for (x = 0; x < res_x; ++x) {

		HANDLE_MALLOC(cost_col, SIZE_COL);

		for (y = 0; y < res_y; ++y) {


			cost_col[y] = grad;
		}

		cost_grid[x] = cost_col;

	}


	return cost_grid;
}


double perlin_noise(const size_t x0,
		    const size_t y0,
		    double ***grad_grid)
{
	const size_t x1 = x0 + 1lu;
	const size_t y1 = y0 + 1lu;

	double grad0;
	double grad1;
	double dxdy_dot_grad0;
	double dxdy_dot_grad1;

	grad0 = grad_grid[x0][y0];
	grad1 = grad_grid[x1][y0];

	dxdy_dot_grad0 = dot_prod_2d( 0.5, -0.5, grad0[0], grad0[1]);
	dxdy_dot_grad1 = dot_prod_2d( 0.5,  0.5, grad1[0], grad1[1]);

	const double lerp_NW_NE = linear_interp_step(dxdy_dot_grad0,
						     dxdy_dot_grad1, 0.5);

	grad0 = grad_grid[x0][y1];
	grad1 = grad_grid[x1][y1];

	dxdy_dot_grad0 = dot_prod_2d(-0.5, -0.5, grad0[0], grad0[1]);
	dxdy_dot_grad1 = dot_prod_2d(-0.5,  0.5, grad1[0], grad1[1]);

	const double lerp_SW_SE = linear_interp_step(dxdy_dot_grad0,
						     dxdy_dot_grad1, 0.5);


	return linear_interp_step(lerp_NW_NE,
				  lerp_SW_SE, 0.5);
}

inline double dot_prod_2d(const double u_x, const double u_y,
			  const double v_x, const double v_y)
{
	return (u_x * v_x) + (u_y * v_y);
}

/* linearly interpolate between 'lbound' and 'rbound' according to
 * '0.0 <= weight <= 1.0'
 ******************************************************************************/
inline double linear_interp_step(const double lbound,
				 const double rbound,
				 const double weight)
{
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
	double **grad_col;
	double *grad;
	double u, v;
	size_t x, y;

	const size_t SIZE_COL  = sizeof(double *) * verts_y;
	const size_t SIZE_GRAD = sizeof(double)   * 2lu;


	HANDLE_MALLOC(grad_grid, sizeof(double **) * verts_x);

	for (x = 0; x < verts_x; ++x) {

		HANDLE_MALLOC(grad_col, SIZE_COL);

		for (y = 0; y < verts_y; ++y) {

			HANDLE_MALLOC(grad, SIZE_GRAD);

			u = rand_in_dub_range(-1.0, 1.0);
			v = sqrt(1.0 - (u * u));

			grad[0] = u;
			grad[1] = coin_flip() ? v : -v;

			grad_col[y] = grad;
		}

		grad_grid[x] = grad_col;
	}

	return grad_grid;
}
