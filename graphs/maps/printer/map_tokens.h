#ifndef _GRAPHS_MAPS_PRINTER_MAP_TOKENS_H_
#define _GRAPHS_MAPS_PRINTER_MAP_TOKENS_H_
#include "utils/token.h"

#define MAX_COST_TOKEN_SIZE 13lu

void set_cost_token_0(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_CHAR(ptr, ' ');

	*dbl_ptr = ptr;
}

void set_cost_token_1(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_FAINT(ptr);
	PUT_ANSI_BLACK(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 1);

	*dbl_ptr = ptr;
}
void set_cost_token_2(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_FAINT(ptr);
	PUT_ANSI_BLUE(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 2);

	*dbl_ptr = ptr;
}

void set_cost_token_3(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_CYAN(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 3);

	*dbl_ptr = ptr;
}

void set_cost_token_4(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_GREEN(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 4);

	*dbl_ptr = ptr;
}

void set_cost_token_5(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_YELLOW(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 5);

	*dbl_ptr = ptr;
}

void set_cost_token_6(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_BRIGHT(ptr);
	PUT_ANSI_RED(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 6);

	*dbl_ptr = ptr;
}

void set_cost_token_7(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_BRIGHT(ptr);
	PUT_ANSI_MAGENTA(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 7);

	*dbl_ptr = ptr;
}

void set_cost_token_8(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_BRIGHT(ptr);
	PUT_ANSI_BLACK(ptr);
	PUT_BLOCK_CHAR_BASE_FILL(ptr, 8);

	*dbl_ptr = ptr;
}

const void (*COST_TOKEN_SETTERS[9])(char **) = {
	set_cost_token_0, set_cost_token_1, set_cost_token_2, set_cost_token_3,
	set_cost_token_4, set_cost_token_5, set_cost_token_6, set_cost_token_7,
	set_cost_token_8
}
#endif /* ifndef _GRAPHS_MAPS_PRINTER_MAP_TOKENS_H_
