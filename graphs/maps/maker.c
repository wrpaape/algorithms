#include "utils/utils.h"
#include "utils/rand.h"
#include "maps/maker.h"
#include <math.h>

extern inline void free_cost_map(struct CostMap *map);

struct CostMap *make_cost_map(const size_t char_width,
			      const size_t char_height,
			      const int min_cost,
			      const int max_cost)
{
	char min_str[6];
	char max_str[6];

	sprintf(min_str, "%d", min_cost);
	sprintf(max_str, "%d", max_cost);

	const size_t min_str_len = strlen(min_str);
	const size_t max_str_len = strlen(max_str);

	const size_t col_width = (min_str_len > max_str_len ?
				  min_str_len : max_str_len) + 2lu;

	const size_t res_x = (char_height - 1lu) / 2lu;

	if (res_x == 0lu) {
		EXIT_ON_FAILURE("map must be at least 3 characters tall"
				" (input height: %zu)", char_height);
	}

	const size_t res_y = (char_width  - 1lu) / (col_width + 1lu);

	if (res_y == 0lu) {
		EXIT_ON_FAILURE("map must be at least %zu characters wide"
				" (input width: %zu)",
				col_width + 2lu, char_width);
	}


	struct CostMap *map;
	int **costs;
	int *cost_row;
	int cost;
	size_t x, y;

	int actual_min = max_cost;
	int actual_max = min_cost;

	costs = make_costs(res_x, res_y, min_cost, max_cost);

	for (x = 0; x < res_x; ++x) {

		cost_row = costs[x];

		for (y = 0; y < res_y; ++y) {

			cost = cost_row[y];

			if (cost < actual_min)
				actual_min = cost;

			else if (cost > actual_max)
				actual_max = cost;
		}
	}


	HANDLE_MALLOC(map, sizeof(struct CostMap));

	map->costs = costs;
	map->res_x = res_x;
	map->res_y = res_y;
	map->min_cost = actual_min;
	map->max_cost = actual_max;
	map->col_width = col_width;

	return map;
}


int **make_costs(const size_t res_x,
		 const size_t res_y,
		 const int min_cost,
		 const int max_cost)
{

	const size_t verts_x = res_x + 1lu;
	const size_t verts_y = res_y + 1lu;

	init_rng();

	double ***grad_grid = init_grad_grid(verts_x, verts_y);

	int **costs = init_costs(res_x, res_y,
				 (double) min_cost,
				 (double) max_cost,
				 grad_grid);

	free_grad_grid(verts_x, verts_y, grad_grid);

	return costs;
}


int **init_costs(const size_t res_x,
		 const size_t res_y,
		 const double min_cost,
		 const double max_cost,
		 double ***grad_grid)
{
	const double cost_diff = max_cost - min_cost;

	int **costs_map;
	int *costs_row;
	double noise;
	double est_cost;
	size_t x, y;


	HANDLE_MALLOC(costs_map, sizeof(int *) * res_x);
	const size_t SIZE_ROW  = sizeof(int)   * res_y;

	for (x = 0; x < res_x; ++x) {

		HANDLE_MALLOC(costs_row, SIZE_ROW);

		for (y = 0; y < res_y; ++y) {

			noise = (perlin_noise(x, y, grad_grid) + 1.0) / 2.0;

			est_cost = min_cost + (cost_diff * noise);

			costs_row[y] = (int) round(est_cost);
		}

		costs_map[x] = costs_row;
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
	double **grad_row;
	double *grad;
	double u, v;
	size_t x, y;


	HANDLE_MALLOC(grad_grid, sizeof(double **) * verts_x);
	const size_t SIZE_ROW  = sizeof(double *)  * verts_y;
	const size_t SIZE_GRAD = sizeof(double)    * 2lu;

	for (x = 0; x < verts_x; ++x) {

		HANDLE_MALLOC(grad_row, SIZE_ROW);

		for (y = 0; y < verts_y; ++y) {

			HANDLE_MALLOC(grad, SIZE_GRAD);

			u = rand_in_dub_range(-1.0, 1.0);
			v = sqrt(1.0 - (u * u));

			grad[0] = u;
			grad[1] = coin_flip() ? v : -v;

			grad_row[y] = grad;
		}

		grad_grid[x] = grad_row;
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
	double **grad_row;
	size_t x, y;

	for (x = 0; x < verts_x; ++x) {

		grad_row = grad_grid[x];

		for (y = 0; y < verts_y; ++y)
			free(grad_row[y]);

		free(grad_row);
	}

	free(grad_grid);
}
