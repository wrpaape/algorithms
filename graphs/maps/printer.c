#include "utils/utils.h"
#include "maps/maker.h"
#include "maps/printer.h"


#define SET_CHAR(PTR, BYTE)						\
do {									\
	*PTR = BYTE;							\
	++PTR;								\
} while (0)

#define SET_BOX_CHAR(PTR, BYTE)						\
do {									\
	SET_CHAR(PTR, 226);						\
	SET_CHAR(PTR, 148);						\
	SET_CHAR(PTR, BYTE);						\
} while (0)

#define HANDLE_FOPEN(FILE_PTR, FILENAME, MODE)				\
do {									\
	FILE_PTR = fopen(FILENAME, MODE);				\
	if (FILE_PTR == NULL)						\
		EXIT_ON_FAILURE("failed to open file '%s' (mode '%s')",	\
				FILENAME, MODE);			\
} while (0)


struct Lines {
	char *top;
	char *mid;
	char *bot;
};

/* y_ratio > 0.85 -> ANSI.bright <> ANSI.magenta */
/* y_ratio > 0.70 -> ANSI.bright <> ANSI.red */
/* y_ratio > 0.55 ->                ANSI.yellow */
/* y_ratio > 0.40 ->                ANSI.green */
/* y_ratio > 0.20 -> ANSI.faint  <> ANSI.cyan */
/* true           -> ANSI.faint  <> ANSI.blue */

void pretty_print_cost_map(char *buffer,
			   struct CostMap *map)
{
	const char *BLOCKS[] = {
		" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"
	};

	/* const size_t row_width = res_y * (col_width + 1lu); */

	/* char buffer[res_x * row_width]; */

	const int res_x  = map->res_x;
	const int res_y  = map->res_y;

	FILE *map_file;
	int **costs;
	int *costs_row;
	struct Lines *lines;
	char *mid_line;
	size_t x, y;


	costs = map->costs;

	lines    = draw_lines(res_x);
	mid_line = lines->mid;


/* 	fputs(lines->top, map_file); */

/* 	x = 0lu; */

/* 	while (1) { */
/* 		fputs("│", map_file); */

/* 		costs_row = costs[x]; */

/* 		for (y = 0lu; y < res_y; ++y) */
/* 			fprintf(map_file, " %s │", BLOCKS[costs_row[y]]); */

/* 		fputc('\n', map_file); */

/* 		++x; */

/* 		if (x == res_x) */
/* 			break; */

/* 		fputs(mid_line, map_file); */
/* 	} */

/* 	fputs(lines->bot, map_file); */

/* 	fclose(map_file); */
}

void cost_map_to_csv(char *filename,
		     struct CostMap *map)
{
	const size_t res_x = map->res_x;
	const size_t res_y = map->res_y;


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

	struct Lines *lines;
	char *top;
	char *mid;
	char *bot;
	size_t cell_i;
	size_t char_i;

	HANDLE_MALLOC(lines, sizeof(struct Lines));
	HANDLE_MALLOC(top,   sizeof(char) * BUFF_CHARS);
	HANDLE_MALLOC(mid,   sizeof(char) * BUFF_CHARS);
	HANDLE_MALLOC(bot,   sizeof(char) * BUFF_CHARS);

	lines->top = top;
	lines->mid = mid;
	lines->bot = bot;


	/* set left pieces '┌', '├', and '└' */
	SET_BOX_CHAR(top, 140);
	SET_BOX_CHAR(mid, 156);
	SET_BOX_CHAR(bot, 148);

	cell_i = 1lu;

	while (1) {

		/* set 3 horizontal lines '─' (top/bottom borders of cells) */
		for (char_i = 0lu; char_i < 3lu; ++char_i) {
			SET_BOX_CHAR(top, 128);
			SET_BOX_CHAR(mid, 128);
			SET_BOX_CHAR(bot, 128);
		}

		/* if on last cell... */
		if (cell_i == res_x)
			break; /* break, terminate lines and return */

		/* otherwise set joiner pieces '┬', '┼', and '┴' */
		SET_BOX_CHAR(top, 172);
		SET_BOX_CHAR(mid, 188);
		SET_BOX_CHAR(bot, 180);

		++cell_i;
	}

	/* set right pieces '┐', '┤', and '┘' */
	SET_BOX_CHAR(top, 144);
	SET_BOX_CHAR(mid, 164);
	SET_BOX_CHAR(bot, 152);

	/* terminate with newlines and null byte */
	SET_CHAR(top, '\n'); SET_CHAR(top, '\0');
	SET_CHAR(mid, '\n'); SET_CHAR(mid, '\0');
	SET_CHAR(bot, '\n'); SET_CHAR(bot, '\0');

	return lines;
}
