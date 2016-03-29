#ifndef GRAPHS_MAPS_GENERATOR_H_
#define GRAPHS_MAPS_GENERATOR_H_ value
int **generate_map(const size_t res_x,
		   const size_t res_y,
		   const int min_cost,
		   const int max_cost);

int ***init_grad_grid(const size_t res_x,
		      const size_t res_y);
#endif /* ifndef GRAPHS_MAPS_GENERATOR_H_ */
