#include <stdio.h>
#include "token.h"

#define BUFF_SIZE (1ul << 5)

int main(void)
{
	char input[BUFF_SIZE];

	fputs("check for unmatching parentheses\n"
	      ANSI_BLINK "> " ANSI_BLINK_OFF, stdout);

	fgets(&input[0], BUFF_SIZE, stdin);

	puts(input);

	return 0;
}
