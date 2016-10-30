#include <stdio.h>


enum Color {
	RED,
	WHITE,
	BLUE
};

void
print_array(const enum Color *restrict color,
	    const size_t length)
{
	static const char color_strings[] = {
		[RED]	= "RED",
		[WHITE] = "WHITE",
		[BLUE]	= "BLUE"
	};

	if (length == 0) {
		puts("colors = {};");
		return;
	}

	printf("colors = {\n\t%s",
	       color_strings[*color]);


	const enum Color *const restrict until = color + length;

	while (1) {
		++color;
		if (color == until) {
			puts("\n};");
			return;
		}

		printf(", %s",
		       color_strings[*color]);
	}
}

void
swap(enum Color *const restrict x,
     enum Color *const restrict y)
{
	const enum Color tmp = *x;
	*x = *y;
	*y = tmp;
}

void
do_dutch_sort(enum Color *restrict red_bound,
	      enum Color *restrict blue_bound)
{
	enum Color *restrict white_bound;
	enum Color color;


	while (1) {
		while (*red_bound == RED) {
			++red_bound;
			if (red_bound == blue_bound)
				return;
		}

		while (*blue_bound == BLUE) {
			--blue_bound;
			if (blue_bound == red_bound)
				return;
		}


		if (*red_bound == WHITE) {
			white_bound = red_bound;

			while (1) {
				++white_bound;
				if (white_bound == blue_bound) {
					swap(red_bound,
					     blue_bound);

					return;
				}

				color = *white_bound;

				if (color == RED) {
					swap(red_bound,
					     white_bound);

					++red_bound;

				} else if (color == BLUE) {

					if (*blue_bound == WHITE)
					swap(white_bound,
					     blue_bound);
				}
			}






		} else if (*blue_bound == WHITE) {

		} else {
			swap(red_bound,
			     blue_bound);

			++red_bound;
			if (red_bound == blue_bound)
				return;

			--blue_bound;
			if (blue_bound == red_bound)
				return;
		}
	}
}

void
dutch_sort(enum Color *const restrict colors,
	   const size_t length)
{
	if (length > 1) {
		do_dutch_sort(colors,
			      colors + length - 1);
	}
}


int
main(void)
{
	enum Color colors[21] = {
		RED, WHITE, BLUE, BLUE, RED, BLUE, WHITE,
		WHITE, RED, BLUE, BLUE, WHITE, WHITE, RED,
		BLUE, RED, RED, RED, WHITE, BLUE, RED
	};

	print_array(&colors[0],
		    21);

	dutch_sort(&colors[0],
		   21);

	print_array(&colors[0],
		    21);

	return 0;
}
