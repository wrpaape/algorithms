#ifndef GRAPHS_MAPS_GENERATOR_H_
#define GRAPHS_MAPS_GENERATOR_H_ value
int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost);

double ***init_grad_grid(const size_t verts_x,
			 const size_t verts_y);

static inline double smoothstep(const double ledge,
				const double redge,
				const double x)

#endif /* ifndef GRAPHS_MAPS_GENERATOR_H_ */
