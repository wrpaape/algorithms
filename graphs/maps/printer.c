#include "utils/utils.h"
#include "maps/maker.h"
#include "maps/printer.h"
#include "maps/printer/map_tokens.h"

#define PAD_SIZE 2lu
#define HANDLE_FOPEN(FILE_PTR, FILENAME, MODE)				\
do {									\
	FILE_PTR = fopen(FILENAME, MODE);				\
	if (FILE_PTR == NULL)						\
		EXIT_ON_FAILURE("failed to open file '%s' (mode '%s')",	\
				FILENAME, MODE);			\
} while (0)



void pretty_print_cost_map(char *buffer,
			   struct CostMap *map)
{
	const size_t res_x = map->res->x;
	const size_t res_y = map->res->y;

	const int min_cost = map->est_bounds->min;
	const int max_cost = map->est_bounds->max;

	const double token_ratio = ((double) TOKEN_SPAN)
				 / ((double) (max_cost - min_cost));

	const int start_x = map->start->x;
	const int start_y = map->start->y;

	const int goal_x = map->goal->x;
	const int goal_y = map->goal->y;

	int **costs = map->costs;

	const size_t num_char_rows = res_x * 2lu + 1lu;

	int *cost_row;
	size_t x, y;



	x = 0lu;


	while (1) {

		buff_ptr = cell_buff;

		PUT_ANSI_WHITE_BG(buff_ptr);
		PUT_BOX_CHAR_LIGHT_V_LINE(buff_ptr);

	}




	COST_TOKEN_SETTERS[4](&buffer);
	COST_TOKEN_SETTERS[4](&buffer);
	COST_TOKEN_SETTERS[4](&buffer);
	COST_TOKEN_SETTERS[4](&buffer);
	set_start_token(&buffer);
	COST_TOKEN_SETTERS[5](&buffer);
	COST_TOKEN_SETTERS[6](&buffer);
	COST_TOKEN_SETTERS[0](&buffer);
	set_goal_token(&buffer);

	puts(lines->top);
	puts(lines->mid);
	puts(lines->bot);

	free_lines(lines);
	/* *buffer = '\0'; */

}

void cost_map_to_csv(char *filename,
		     struct CostMap *map)
{
	const size_t res_x = map->res->x;
	const size_t res_y = map->res->y;


	FILE *map_file;
	int **costs;
	int *cost_row;
	size_t x, y;

	HANDLE_FOPEN(map_file, filename, "w");

	costs = map->costs;

	x = 0lu;

	while (1) {
		cost_row = costs[x];

		y = 0lu;

		while (1) {
			fprintf(map_file, "%d", cost_row[y]);

			++y;

			if (y == res_y)
				break;

			fputc(',', map_file);
		}

		++x;

		if (x == res_x)
			break;

		fputc('\n', map_file);
	}


	fclose(map_file);
}
