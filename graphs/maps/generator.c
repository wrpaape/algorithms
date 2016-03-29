#include "utils/utils.h"
#include "utils/rand.h"
#include "maps/generator.h"
#include <math.h>

int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost)
{

	const size_t verts_x = res_x + 1lu;
	const size_t verts_y = res_y + 1lu;

	init_rng();

	double ***grad_grid = init_grad_grid(verts_x, verts_y);

	int **costs_map = init_costs_map(res_x, res_y,
					 (double) min_cost,
					 (double) max_cost,
					 grad_grid);

	free_grad_grid(verts_x, verts_y, grad_grid);

	return costs_map;
}


int **init_costs_map(const size_t res_x,
		     const size_t res_y,
		     const double min_cost,
		     const double max_cost,
		     double ***grad_grid)
{
	const double cost_diff = max_cost - min_cost;

	int **costs_map;
	int *costs_col;
	double noise;
	double est_cost;
	size_t x, y;


	HANDLE_MALLOC(costs_map, sizeof(int *) * res_y);
	const size_t SIZE_COL  = sizeof(int)   * res_x;

	for (x = 0; x < res_x; ++x) {

		HANDLE_MALLOC(costs_col, SIZE_COL);

		for (y = 0; y < res_y; ++y) {

			noise = (perlin_noise(x, y, grad_grid) + 1.0) / 2.0;

			est_cost = min_cost + (cost_diff * noise);

			costs_col[y] = (int) round(est_cost);
		}

		costs_map[x] = costs_col;
	}


	return costs_map;
}

double perlin_noise(const size_t x0,
		    const size_t y0,
		    double ***grad_grid)
{
	const size_t x1 = x0 + 1lu;
	const size_t y1 = y0 + 1lu;

	double *grad0;
	double *grad1;
	double dxdy_dot_grad0;
	double dxdy_dot_grad1;

	grad0 = grad_grid[x0][y0];
	grad1 = grad_grid[x1][y0];

	dxdy_dot_grad0 = dot_prod_2d( 0.5, -0.5, grad0[0], grad0[1]);
	dxdy_dot_grad1 = dot_prod_2d( 0.5,  0.5, grad1[0], grad1[1]);

	const double avg_NW_NE = (dxdy_dot_grad0 + dxdy_dot_grad1) / 2.0;

	grad0 = grad_grid[x0][y1];
	grad1 = grad_grid[x1][y1];

	dxdy_dot_grad0 = dot_prod_2d(-0.5, -0.5, grad0[0], grad0[1]);
	dxdy_dot_grad1 = dot_prod_2d(-0.5,  0.5, grad1[0], grad1[1]);

	const double avg_SW_SE = (dxdy_dot_grad0 + dxdy_dot_grad1) / 2.0;

	return (avg_NW_NE + avg_SW_SE) / 2.0;
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


	HANDLE_MALLOC(grad_grid, sizeof(double **) * verts_x);
	const size_t SIZE_COL  = sizeof(double *) * verts_y;
	const size_t SIZE_GRAD = sizeof(double)   * 2lu;

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

/* helper functions
 ******************************************************************************/

inline double dot_prod_2d(const double u_x, const double u_y,
			  const double v_x, const double v_y)
{
	return (u_x * v_x) + (u_y * v_y);
}

inline void free_grad_grid(const size_t verts_x,
			   const size_t verts_y,
			   double ***grad_grid)
{
	double **grad_col;
	size_t x, y;

	for (x = 0; x < verts_x; ++x) {

		grad_col = grad_grid[x];

		for (y = 0; y < verts_y; ++y)
			free(grad_col[y]);

		free(grad_col);
	}

	free(grad_grid);
}
