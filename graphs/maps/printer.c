#include "utils/utils.h"
#include "maps/maker.h"
#include "maps/printer.h"
#include "maps/printer/map_tokens.h"

#define PAD_SIZE 2lu
#define SETTER_COUNT 9lu

#define HANDLE_FOPEN(FILE_PTR, FILENAME, MODE)				\
do {									\
	FILE_PTR = fopen(FILENAME, MODE);				\
	if (FILE_PTR == NULL)						\
		EXIT_ON_FAILURE("failed to open file '%s' (mode '%s')",	\
				FILENAME, MODE);			\
} while (0)

void (*COST_TOKEN_SETTERS[SETTER_COUNT])(char **) = {
	set_cost_token_0, set_cost_token_1, set_cost_token_2, set_cost_token_3,
	set_cost_token_4, set_cost_token_5, set_cost_token_6, set_cost_token_7,
	set_cost_token_8
};



void pretty_print_cost_map(char *buffer,
			   struct CostMap *map)
{
	const size_t res_x  = map->resolution->x;
	const size_t res_y  = map->resolution->y;

	const int min_cost = map->est_bounds->min;
	const int max_cost = map->est_bounds->max;

	const size_t num_char_rows = res_y * 2lu + 1lu;

	const size_t max_row_size = (MAX_COST_TOKEN_SIZE * (res_x - 2lu))
				  + START_TOKEN_SIZE
				  + GOAL_TOKEN_SIZE
				  + ((PAD_SIZE + BOX_CHAR_SIZE) * res_x)
				  + (BOX_CHAR_SIZE + 1lu);
	int **costs;
	int *costs_row;
	struct Lines *lines;
	char *mid_line;
	size_t x, y;

	COST_TOKEN_SETTERS[5](&buffer);

	*buffer = '\0';
}

void cost_map_to_csv(char *filename,
		     struct CostMap *map)
{
	const size_t res_x = map->resolution->x;
	const size_t res_y = map->resolution->y;


	FILE *map_file;
	int **costs;
	int *costs_row;
	size_t x, y;

	HANDLE_FOPEN(map_file, filename, "w");

	costs = map->costs;

	x = 0lu;

	while (1) {
		costs_row = costs[x];

		y = 0lu;

		while (1) {
			fprintf(map_file, "%d", costs_row[y]);

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


struct Lines *draw_lines(const size_t res_x)
{
	/* 'res_x * 4': length of  '───' plus joiner */
	/* '_____ + 1': plus left piece */
	/* '_____ * 3': 3 bytes per box drawing character */
	/* '_____ + 2': newline plus null byte */
	const size_t BUFF_CHARS = (((res_x * 4lu) + 1lu) * 3lu) + 2lu;

	const size_t size = sizeof(char) * BUFF_CHARS;

	struct Lines *lines;
	char *top;
	char *mid;
	char *bot;
	size_t cell_i;
	size_t char_i;

	HANDLE_MALLOC(lines, sizeof(struct Lines));
	HANDLE_MALLOC(top,   size);
	HANDLE_MALLOC(mid,   size);
	HANDLE_MALLOC(bot,   size);

	lines->top = top;
	lines->mid = mid;
	lines->bot = bot;
	lines->size = size;

	/* set white_bg ANSI */

	/* set left pieces '┌', '├', and '└' */
	PUT_BOX_CHAR_LIGHT_NW_CORNER(top);
	PUT_BOX_CHAR_LIGHT_W_JOIN(mid);
	PUT_BOX_CHAR_LIGHT_SW_CORNER(bot);
	/* PUT_BOX_CHAR(top, 140); */
	/* PUT_BOX_CHAR(mid, 156); */
	/* PUT_BOX_CHAR(bot, 148); */

	cell_i = 1lu;

	while (1) {

		/* set 3 horizontal lines '─' (top/bottom borders of cells) */
		for (char_i = 0lu; char_i < 3lu; ++char_i) {
			PUT_BOX_CHAR_LIGHT_H_LINE(top);
			PUT_BOX_CHAR_LIGHT_H_LINE(mid);
			PUT_BOX_CHAR_LIGHT_H_LINE(bot);
			/* PUT_BOX_CHAR(top, 128); */
			/* PUT_BOX_CHAR(mid, 128); */
			/* PUT_BOX_CHAR(bot, 128); */
		}

		/* if on last cell... */
		if (cell_i == res_x)
			break; /* break, terminate lines and return */

		/* otherwise set joiner pieces '┬', '┼', and '┴' */
		PUT_BOX_CHAR_LIGHT_N_JOIN(top);
		PUT_BOX_CHAR_LIGHT_CROSS(mid);
		PUT_BOX_CHAR_LIGHT_S_JOIN(bot);
		/* PUT_BOX_CHAR(top, 172); */
		/* PUT_BOX_CHAR(mid, 188); */
		/* PUT_BOX_CHAR(bot, 180); */

		++cell_i;
	}

	/* set right pieces '┐', '┤', and '┘' */
	PUT_BOX_CHAR_LIGHT_NE_CORNER(top);
	PUT_BOX_CHAR_LIGHT_E_JOIN(mid);
	PUT_BOX_CHAR_LIGHT_SW_CORNER(bot);
	/* PUT_BOX_CHAR(top, 144); */
	/* PUT_BOX_CHAR(mid, 164); */
	/* PUT_BOX_CHAR(bot, 152); */

	/* terminate with newlines and null byte */
	PUT_CHAR(top, '\n'); PUT_CHAR(top, '\0');
	PUT_CHAR(mid, '\n'); PUT_CHAR(mid, '\0');
	PUT_CHAR(bot, '\n'); PUT_CHAR(bot, '\0');

	return lines;
}

inline void free_lines(struct Lines *lines)
{
	free(lines->top);
	free(lines->mid);
	free(lines->bot);
	free(lines);
}
