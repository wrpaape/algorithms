#include "utils.h"
#include "maps/generator.h"
#include "maps/printer.h"

#define FILENAME "maps/map.txt"

#define SET_CHAR(PTR, BYTE)	\
do {				\
	*PTR = BYTE;		\
	++PTR;			\
} while (0)

#define SET_BOX_CHAR(PTR, BYTE)	\
do {				\
	SET_CHAR(PTR, 226);	\
	SET_CHAR(PTR, 148);	\
	SET_CHAR(PTR, BYTE);	\
} while (0)

struct Lines {
	char *top;
	char *mid;
	char *bot;
};

void print_map(const size_t width,
	       const size_t height)
{
	const size_t res_x = (width  - 1lu) / 4lu;

	if (res_x == 0lu) {
		EXIT_ON_FAILURE("map width must be at least 5 characters"
				" (input width: %zu)", width);
	}

	const size_t res_y = (height - 1lu) / 2lu;

	if (res_x == 0lu) {
		EXIT_ON_FAILURE("map height must be at least 3 characters"
				" (input height: %zu)", width);
	}


	FILE *map_file = fopen(FILENAME, "w");

	if (map_file == NULL)
		EXIT_ON_FAILURE("failed to open file '%s'", FILENAME);

	struct Lines *lines = draw_lines(res_x);
	int **costs_grid    = generate_map(res_x, res_y, 0, 9);

	fputs("test\n\n", map_file);
	fputs(lines->top, map_file);
	fputs(lines->mid, map_file);
	fputs(lines->bot, map_file);

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

	lines->top = top; lines->mid = mid; lines->bot = bot;


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
