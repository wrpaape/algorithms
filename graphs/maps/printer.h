#ifndef GRAPHS_MAPS_PRINTER_H_
#define GRAPHS_MAPS_PRINTER_H_
struct Lines {
	char *top;
	char *mid;
	char *bot;
	size_t size;
};

struct Token {
	char *chars;
	size_t size;
}

void pretty_print_cost_map(char *buffer,
			   struct CostMap *map);

void cost_map_to_csv(char *filename,
		     struct CostMap *map);

struct Lines *draw_lines(const size_t res_x);

static inline void free_lines(struct Lines *lines);

#endif /* ifndef GRAPHS_MAPS_PRINTER_H_ */

/*****************************************************************************
 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 *
 *****************************************************************************
 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 * 1 *
 ******************************************************************************/


	/* ╔╦╗╠╬╣╚╩╝|═║┌┬┐│─├┼┤└┴┘┏┳┓┣╋┫┗┻┻┛━┃ */

/* [{"┌", "<<226, 148, 140>>"}, {"┬", "<<226, 148, 172>>"}, */
/*  {"┐", "<<226, 148, 144>>"}, {"│", "<<226, 148, 130>>"}, */
/*  {"─", "<<226, 148, 128>>"}, {"├", "<<226, 148, 156>>"}, */
/*  {"┼", "<<226, 148, 188>>"}, {"┤", "<<226, 148, 164>>"}, */
/*  {"└", "<<226, 148, 148>>"}, {"┴", "<<226, 148, 180>>"}, */
/*  {"┘", "<<226, 148, 152>>"}] */
