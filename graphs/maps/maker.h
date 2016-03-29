#ifndef GRAPHS_MAPS_MAKER_H_
#define GRAPHS_MAPS_MAKER_H_

struct Coords {
	size_t x;
	size_t y;
};

struct Bounds {
	int min;
	int max;
};

struct CostMap {
	struct Coords *resolution;
	struct Coords *start_coords;
	struct Coords *goal_coords;
	struct Bounds *est_bounds;
	struct Bounds *act_bounds;
	int **costs;
};

struct CostMap *make_cost_map(const size_t char_width,
			      const size_t char_height,
			      const int min_cost,
			      const int max_cost);

void set_start_and_goal(const size_t res_x,
			const size_t res_y,
			struct Coords *start_coords,
			struct Coords *goal_coords);

double ***init_grad_grid(const size_t verts_x,
			 const size_t verts_y);

int **init_costs(const size_t res_x,
		 const size_t res_y,
		 const double min_cost,
		 const double max_cost,
		 double ***grad_grid);

int **make_costs(const size_t res_x,
		 const size_t res_y,
		 const int min_cost,
		 const int max_cost);

double perlin_noise(const size_t x_0,
		    const size_t y_0,
		    double ***grad_grid);

static inline double dot_prod_2d(const double u_x, const double u_y,
				 const double v_x, const double v_y);

static inline void free_grad_grid(const size_t verts_x,
				  const size_t verts_y,
				  double ***grad_grid);

inline void free_cost_map(struct CostMap *map)
{
	int **costs = map->costs;

	for (size_t x = 0lu, res_x = map->resolution->x; x < res_x; ++x)
		free(costs[x]);

	free(costs);
	free(map->resolution);
	free(map->start_coords);
	free(map->goal_coords);
	free(map->est_bounds);
	free(map->act_bounds);
	free(map);
}
#endif /* ifndef GRAPHS_MAPS_MAKER_H_ */
