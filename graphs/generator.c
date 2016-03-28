#include <rand.h>
#include "graphs.h"
#include "generator.h"

#define FILENAME "map.txt"

struct Lines {
	char *top;
	char *mid;
	char *bot;
};

	/* ╔╦╗╠╬╣╚╩╝|═║┌┬┐├┼┤└┴┘┏┳┓┣╋┫┗┻┻┛━┃ */

void generate_map(const size_t width, const size_t height)
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


	struct Lines *borders = init_lines(res_x);

	FILE *map_file = fopen(FILENAME, "w");

	if (map_file == NULL)
		EXIT_ON_FAILURE("failed to open file '%s'", FILENAME);


	fputs("│")
}

struct Lines *init_lines(const size_t res_x)
{
	const size_t BUFF_CHARS = (((res_x * 4lu) + 1lu) * 3lu) + 1lu;

	struct Lines *borders;
	char *top;
	char *mid;
	char *bot;

	HANDLE_MALLOC(borders, sizeof(struct Lines));
	HANDLE_MALLOC(top, sizeof(char) * BUFF_CHARS);
	HANDLE_MALLOC(mid, sizeof(char) * BUFF_CHARS);
	HANDLE_MALLOC(bot, sizeof(char) * BUFF_CHARS);

	borders->top = top;
	borders->mid = mid;
	borders->bot = bot;

	int cell_i;
	int char_i;

	*top

	for (cell_i = 0; i < BUFF_CHARS; ++i) {



	}


}
