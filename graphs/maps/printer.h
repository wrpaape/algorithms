#ifndef GRAPHS_MAPS_PRINTER_H_
#define GRAPHS_MAPS_PRINTER_H_
struct Lines {
	char *top;
	char *mid;
	char *bot;
	size_t size;
};

void pretty_print_cost_map(char *buffer,
			   struct CostMap *map);

void cost_map_to_csv(char *filename,
		     struct CostMap *map);

struct Lines *draw_lines(const size_t res_x);

/* static inline void free_lines(struct Lines *lines); */

#endif /* ifndef GRAPHS_MAPS_PRINTER_H_ */
