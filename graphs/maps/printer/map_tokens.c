#include "maps/printer/map_tokens.h"
#include "utils/token.h"

#define MAX_COST_TOKEN_SIZE 13lu

/* 12-13 bytes */
/* const struct Token COST_TOKENS[] = { */
/* 	{.chars = FAINT  WHITE   "▁", .size = 12lu}, */
/* 	{.chars = FAINT  BLACK   "▁", .size = 12lu}, */
/* 	{.chars = FAINT  BLUE    "▂", .size = 12lu}, */
/* 	{.chars = NORMAL CYAN    "▃", .size = 13lu}, */
/* 	{.chars = NORMAL GREEN   "▄", .size = 13lu}, */
/* 	{.chars = NORMAL YELLOw  "▅", .size = 13lu}, */
/* 	{.chars = BRIGHT RED     "▆", .size = 12lu}, */
/* 	{.chars = BRIGHT MAGENTA "▇", .size = 12lu}, */
/* 	{.chars = BRIGHT BLACK   "█", .size = 12lu} */
/* }; */

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

extern inline void set_start_token(char **dbl_ptr);
extern inline void set_goal_token(char **dbl_ptr);
