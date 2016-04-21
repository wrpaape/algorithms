#include <stdio.h>
#include "parenths.h"
#include "token.h"

#define BUFF_SIZE (1ul << 5)

int main(void)
{
	char input[BUFF_SIZE];

	fputs("check for unmatching parentheses\n"
	      ANSI_BLINK "> " ANSI_BLINK_OFF, stdout);

	fgets(&input[0], BUFF_SIZE, stdin);

	printf("input is %s\n", test_input(input) ? "GOOD" : "BAD");

	return 0;
}

bool test_input(const char *input)
{

	return *input != '\0';

}
