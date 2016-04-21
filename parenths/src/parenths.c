#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* use C linkage */

#include "parenths.h"

#define BUFF_SIZE (1ul << 5)

/* hide the main function during testing */
#ifndef TESTING
int main(void)
{
	char input[BUFF_SIZE];

	fputs("check string for proper parentheses nesting\n"
	      ANSI_BLINK "> " ANSI_BLINK_OFF, stdout);

	fgets(&input[0], BUFF_SIZE, stdin);

	puts("AWOOOGA");

	return 0;
}
#endif

inline void put_color_token(char **d_ptr,
			    void (*put_ansi)(char **),
			    const char token)
{
	char *ptr;

	(*put_ansi)(d_ptr);

	ptr = *d_ptr;

	PUT_CHAR(ptr, token);

	PUT_ANSI_RESET(ptr);

	*d_ptr = ptr;
}

#ifdef __cplusplus
}
#endif /* use C linkage */
