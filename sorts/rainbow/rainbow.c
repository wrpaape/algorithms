#include <stdio.h>

enum Color {
    RED		= 0,
    ORANGE	= 1,
    YELLOW	= 2,
    GREEN	= 3,
    BLUE	= 4,
    INDIGO	= 5,
    VIOLET	= 6
};

void
print_array(const enum Color *restrict color,
	    const size_t length)
{
	static const char *color_strings[] = {
		[RED]	 = "RED",
		[ORANGE] = "ORANGE",
		[YELLOW] = "YELLOW",
		[GREEN]  = "GREEN",
		[BLUE]   = "BLUE",
		[INDIGO] = "INDIGO",
		[VIOLET] = "VIOLET"
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

static inline void
swap(enum Color *const restrict x,
     enum Color *const restrict y)
{
    const enum Color tmp = *x;
    *x = *y;
    *y = tmp;
}

enum Color *
do_partition(enum Color *restrict from,
             enum Color *restrict upto,
             const enum Color partition)
{
    while (*upto == partition) {
        --upto;

        if (upto == from)
            return upto;
    }

    while (1) {
        if (*from == partition) {
            swap(from,
                 upto);

            while (1) {
                --upto;
                if (upto == from)
                    return upto;

                if (*upto != partition)
                    break;
            }
        }

        ++from;

        if (from == upto)
            return upto;
    }
}


void
do_rainbow_sort(enum Color *const restrict from,
                enum Color *restrict upto,
                enum Color partition)
{
    while (1) {
        if (upto <= from)
            return;

        upto = do_partition(from,
                            upto,
                            partition);

        --partition;

        if (partition <= RED)
            return;
    }
}


static inline void
rainbow_sort(enum Color *const restrict colors,
             const size_t length)
{
    do_rainbow_sort(colors,
                    colors + length - 1,
                    VIOLET);
}


void
test_rainbow(enum Color *const restrict colors,
	     const size_t length)
{
	puts("-- DOIN IT --");
	print_array(colors,
		    length);
	rainbow_sort(colors,
		     length);
	print_array(colors,
		    length);
	puts("-- DID IT --");
}



int
main(void)
{
	enum Color colors1[21] = {
		RED, INDIGO, BLUE, ORANGE, RED, BLUE, VIOLET,
		VIOLET, BLUE, BLUE, BLUE, GREEN, YELLOW, RED,
		BLUE, VIOLET, RED, INDIGO, YELLOW, BLUE, RED
	};

	test_rainbow(&colors1[0],
		     21);

	return 0;
}
