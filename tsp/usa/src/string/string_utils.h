#ifndef TSP_USA_STRING_STRING_UTILS
#define TSP_USA_STRING_STRING_UTILS

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stddef.h>	/* size_t, NULL */

inline size_t
string_length(const char *const restrict string)
{
	register const char *restrict ptr = string;

	while (*ptr != '\0')
		++ptr;

	return ptr - string;
}

#endif	/* TSP_USA_STRING_STRING_UTILS */
