#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* use C linkage */

#include "parenths.h"

#define BUFF_SIZE (1ul << 5)




struct ColorNode


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

inline struct ColorNode *init_color_cycle(void)
{
	struct ColorNode *cycle;

	HANDLE_MALLOC(cycle, sizeof(struct ColorNode) * 5ul);

	cycle[0ul].put_prefix = &put_BLUE;    cycle[0ul].next = &cycle[1ul];
	cycle[1ul].put_prefix = &put_CYAN;    cycle[1ul].next = &cycle[2ul];
	cycle[2ul].put_prefix = &put_MAGENTA; cycle[2ul].next = &cycle[3ul];
	cycle[3ul].put_prefix = &put_YELLOW;  cycle[3ul].next = &cycle[4ul];
	cycle[4ul].put_prefix = &put_WHITE;   cycle[4ul].next = &cycle[0ul];

	return cycle;
}

inline void put_token(char **d_ptr,
		      void (*put_prefix)(char **),
		      const char token)
{
	(*put_prefix)(d_ptr);

	char *ptr = *d_ptr;

	PUT_CHAR(ptr, token);
	PUT_ANSI_RESET(ptr);

	*d_ptr = ptr;
}

#ifdef __cplusplus
}
#endif /* use C linkage */
