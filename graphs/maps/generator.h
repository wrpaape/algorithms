#ifndef GRAPHS_MAPS_GENERATOR_H_
#define GRAPHS_MAPS_GENERATOR_H_
int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost);

double ***init_grad_grid(const size_t verts_x,
			 const size_t verts_y);

int **init_costs_map(const size_t res_x,
		     const size_t res_y,
		     const double min_cost,
		     const double max_cost,
		     double ***grad_grid);

double perlin_noise(const size_t x_0,
		    const size_t y_0,
		    double ***grad_grid);

static inline double dot_prod_2d(const double u_x, const double u_y,
				 const double v_x, const double v_y);

static inline void free_grad_grid(const size_t verts_x,
				  const size_t verts_y,
				  double ***grad_grid);
#endif /* ifndef GRAPHS_MAPS_GENERATOR_H_ */
