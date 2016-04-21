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

/* static inline void put_ERROR_prefix(char **d_ptr) */
/* { */
/* 	char *ptr = *d_ptr; */
/* 	PUT_ANSI_BLINK(ptr); */
/* 	PUT_ANSI_RED(ptr); */
/* 	*d_ptr = ptr; */
/* } */

#ifdef __cplusplus
}
#endif /* use C linkage */
