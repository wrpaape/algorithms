#include "utils/utils.h"
#include "maps/maker.h"
#include "maps/printer.h"


#define SET_CHAR(PTR, BYTE)						\
do {									\
	*PTR = BYTE;							\
	++PTR;								\
} while (0)
/* <<27, 91, 51, 55, 109, 0>> */

#define SET_SML_ANSI(PTR, B2)						\
do {									\
	SET_CHAR(PTR, 27);						\
	SET_CHAR(PTR, 97);						\
	SET_CHAR(PTR, B2);						\
	SET_CHAR(PTR, 109);						\
} while (0)

#define SET_BIG_ANSI(PTR, B2, B3)					\
do {									\
	SET_CHAR(PTR, 27);						\
	SET_CHAR(PTR, 97);						\
	SET_CHAR(PTR, B2);						\
	SET_CHAR(PTR, B3);						\
	SET_CHAR(PTR, 109);						\
} while (0)

#define SET_BOX_CHAR(PTR, BYTE)						\
do {									\
	SET_CHAR(PTR, 226);						\
	SET_CHAR(PTR, 148);						\
	SET_CHAR(PTR, BYTE);						\
} while (0)

#define SET_ANSI_WHITE_BG(PTR) SET_BIG_ANSI(PTR, 52, 53)
#define SET_ANSI_RESET(PTR) SET_SML_ANSI(PTR, 48)

#define HANDLE_FOPEN(FILE_PTR, FILENAME, MODE)				\
do {									\
	FILE_PTR = fopen(FILENAME, MODE);				\
	if (FILE_PTR == NULL)						\
		EXIT_ON_FAILURE("failed to open file '%s' (mode '%s')",	\
				FILENAME, MODE);			\
} while (0)

inline void free_lines(struct Lines *lines)
{
	free(lines->top);
	free(lines->mid);
	free(lines->bot);
	free(lines);
}

#define PAD_SIZE 2lu
#define BOX_CHAR_SIZE 3lu

/* 4 bytes */
#define FAINT "\e[2m"
#define BRIGHT "\e[1m"
#define RESET "\e[0m"

/* 5 bytes */
#define NORMAl "\e[22m"
#define WHITE_BG "\e[47m"
#define BLACK_BG "\e[40m"
#define WHITE "\e[37m"
#define BLUE "\e[34m"
#define CYAN "\e[36m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define RED "\e[31m"
#define MAGENTA "\e[35m"
#define BLACK "\e[30m"


/* 12-13 bytes */
#define COST_TOKEN_SIZE 13lu
const struct Token COST_TOKENS[] = {
	{.chars = FAINT  WHITE   "▁", .size = 12lu},
	{.chars = FAINT  BLACK   "▁", .size = 12lu},
	{.chars = FAINT  BLUE    "▂", .size = 12lu},
	{.chars = NORMAL CYAN    "▃", .size = 13lu},
	{.chars = NORMAL GREEN   "▄", .size = 13lu},
	{.chars = NORMAL YELLOw  "▅", .size = 13lu},
	{.chars = BRIGHT RED     "▆", .size = 12lu},
	{.chars = BRIGHT MAGENTA "▇", .size = 12lu},
	{.chars = BRIGHT BLACK   "█", .size = 12lu}
};

/* 22 bytes */
const struct Token START_TOKEN = {
	.chars = BLACK_BG BRIGHT WHITE "◯" WHITE_BG,
	.size = 22lu
}

/* 22 bytes */
const struct Token GOAL_TOKEN = {
	.chars = BLACK_BG BRIGHT WHITE "╳" WHITE_BG,
	.size = 22lu
}

const struct Token GOAL_TOKEN = {
	.chars = BLACK_BG BRIGHT WHITE "╳" WHITE_BG,
	.size = 22lu
}

const struct Token GOAL_TOKEN



/* ╳ <<226, 149, 179>>*/
/* ◯ <<226, 151, 139>> */

void pretty_print_cost_map(char *buffer,
			   struct CostMap *map)
{

	/* const size_t row_width = res_y * (col_width + 1lu); */

	/* char buffer[res_x * row_width]; */

	const size_t res_x  = map->resolution->x;
	const size_t res_y  = map->resolution->y;

	const int min_cost = map->est_bounds->min;
	const int max_cost = map->est_bounds->max;

	int **costs;
	int *costs_row;
	struct Lines *lines;
	char *mid_line;
	size_t x, y;

	const size_t num_char_rows = res_y * 2lu + 1lu;
	const size_t max_row_size = (COST_TOKEN_SIZE * (res_x - 2lu))
				  + START_TOKEN.size
				  + GOAL_TOKEN.size
				  + ((PAD_SIZE + BOX_CHAR_SIZE) * res_x)
				  + (BOX_CHAR_SIZE + 1lu);

	char *row_buff;
	char *lines_and_rows[num_char_rows];

	costs = map->costs;

	lines    = draw_lines(res_x);
	mid_line = lines->mid;


	line_buffs[0] = lines->top;

	x = 0lu;

	while (1) {
		fputs("│", map_file);

		costs_row = costs[x];

		for (y = 0lu; y < res_y; ++y) {
			fprintf(map_file, " %s │", BLOCKS[costs_row[y]]);
		}

		fputc('\n', map_file);

		++x;

		if (x == res_x)
			break;

		fputs(mid_line, map_file);
	}

	fputs(lines->bot, map_file);

	fclose(map_file);
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

	lines->size = size;
	lines->top = top;
	lines->mid = mid;
	lines->bot = bot;

	/* set white_bg ANSI */

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
