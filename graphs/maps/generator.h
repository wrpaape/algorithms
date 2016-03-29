#ifndef GRAPHS_MAPS_GENERATOR_H_
#define GRAPHS_MAPS_GENERATOR_H_ value
int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost);

double perlin_noise(const size_t x_0,
		    const size_t y_0,
		    double ***grad_grid);

double ***init_grad_grid(const size_t verts_x,
			 const size_t verts_y);

static inline double dot_prod_2d(const double u_x, const double u_y,
				 const double v_x, const double v_y);

static inline double linear_interp_step(const double lbound,
					const double rbound,
					const double weight);

static inline double smoothstep(const double ledge,
				const double redge,
				const double x);

#endif /* ifndef GRAPHS_MAPS_GENERATOR_H_ */
