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
	struct Coords *cell_res;
	struct Coords *grid_res;
	struct Coords *start;
	struct Coords *goal;
	struct Bounds *est;
	struct Bounds *act;
	int **costs;
};

struct CostMap *make_cost_map(const size_t char_width,
			      const size_t char_height,
			      const int min_cost,
			      const int max_cost);

void set_start_and_goal(struct Coords *grid_res,
			struct Coords *start,
			struct Coords *goal);

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

	for (size_t x = 0lu, res_x = map->cell_res->x; x < res_x; ++x)
		free(costs[x]);

	free(costs);
	free(map->cell_res);
	free(map->grid_res);
	free(map->start);
	free(map->goal);
	free(map->est);
	free(map->act);
	free(map);
}
#endif /* ifndef GRAPHS_MAPS_MAKER_H_ */
