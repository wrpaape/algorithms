#ifndef GRAPHS_MAPS_PRINTER_H_
#define GRAPHS_MAPS_PRINTER_H_
void print_map(const size_t width,
	       const size_t height);

struct Lines *draw_lines(const size_t res_x);

static inline void free_costs_map(const size_t res_x,
				  int **costs_map);
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
