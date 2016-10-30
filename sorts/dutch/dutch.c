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
	static const char *color_strings[] = {
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
do_dutch_sort(enum Color *restrict from,
	      enum Color *restrict upto)
{
	enum Color color;

	while (*upto == BLUE) {
		--upto;
		if (upto == from)
			return;
	}

	enum Color *const restrict start = from;

	while (1) {
		if (*from == BLUE) {
			swap(from,
			     upto);

			while (1) {
				--upto;
				if (upto == from) {
					if (from == start)
						return;
					else
						goto BLUE_SET;

				} else if (*upto != BLUE) {
					break;
				}
			}
		}

		++from;
		if (from == upto)
			break;
	}

BLUE_SET:
	from = start;

	while (1) {
		while (*from == RED) {
			++from;

			if (from == upto)
				return;
		}


		while (*upto == WHITE) {
			--upto;

			if (upto == from)
				return;
		}

		swap(from,
		     upto);

		++from;
		if (from == upto)
			return;

		--upto;
		if (upto == from) {
			if (*upto == RED)
				swap(upto - 1,
				     upto);

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

void
test_dutch(enum Color *const restrict colors,
	   const size_t length)
{
	puts("-- DOIN IT --");
	print_array(colors,
		    length);
	dutch_sort(colors,
		   length);
	print_array(colors,
		    length);
	puts("-- DID IT --");
}

int
main(void)
{
	enum Color colors1[21] = {
		RED, WHITE, BLUE, BLUE, RED, BLUE, WHITE,
		WHITE, RED, BLUE, BLUE, WHITE, WHITE, RED,
		BLUE, RED, RED, RED, WHITE, BLUE, RED
	};

	enum Color colors2[2] = {
		RED, WHITE
	};

	enum Color colors3[2] = {
		WHITE, RED
	};

	enum Color colors4[2] = {
		BLUE, BLUE
	};

	enum Color colors5[2] = {
		BLUE, WHITE
	};

	enum Color colors6[3] = {
		BLUE, WHITE, RED
	};

	enum Color colors7[7] = {
		BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, WHITE
	};

	test_dutch(&colors1[0],
		   21);
	test_dutch(&colors2[0],
		   2);
	test_dutch(&colors3[0],
		   2);
	test_dutch(&colors4[0],
		   2);
	test_dutch(&colors5[0],
		   2);
	test_dutch(&colors6[0],
		   3);
	test_dutch(&colors7[0],
		   7);

	return 0;
}
