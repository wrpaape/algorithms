#include "maps/printer/map_tokens.h"
#include "utils/token.h"

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

#define PUT_HORIZONTAL_LINES(ptr)	\
do {					\
	PUT_BOX_CHAR_LIGHT_H_LINE(ptr);	\
	PUT_BOX_CHAR_LIGHT_H_LINE(ptr);	\
	PUT_BOX_CHAR_LIGHT_H_LINE(ptr);	\
} while (0)

extern inline void set_start_token(char **dbl_ptr);
extern inline void set_goal_token(char **dbl_ptr);

/* LINE JOIN SETTER FUNCTIONS
 ******************************************************************************/
/* top line
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ */
void set_top_left_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_NW_CORNER(top);
	*dbl_ptr = ptr;
}
void set_top_center_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_N_JOIN(top);
	*dbl_ptr = ptr;
}
void set_top_right_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_NE_CORNER(top);
	*dbl_ptr = ptr;
}

/* mid line
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤ */
void set_mid_left_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_W_JOIN(ptr);
	*dbl_ptr = ptr;
}
void set_mid_center_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_CROSS(ptr);
	*dbl_ptr = ptr;
}
void set_mid_right_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_E_JOIN(ptr);
	*dbl_ptr = ptr;
}


/* bot line
 * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘ */
void set_bot_left_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_SW_CORNER(ptr);
	*dbl_ptr = ptr;
}
void set_bot_center_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_S_JOIN(ptr);
	*dbl_ptr = ptr;
}
void set_bot_right_join(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;
	PUT_BOX_CHAR_LIGHT_SE_CORNER(ptr);
	*dbl_ptr = ptr;
}



/* COMPLETE LINE SETTERS
 ******************************************************************************/
/* unbroken line (top, mid, or bot) */
void set_unbroken_line(char **dbl_ptr,
		       const size_t res_y,
		       struct JoinSetters *join_setters)
{
	char *ptr = *dbl_ptr;

	void (*set_left_join)(char **)	 = join_setters->left;
	void (*set_center_join)(char **) = join_setters->center;
	void (*set_right_join)(char **)  = join_setters->right;

	PUT_ANSI_WHITE_BG(ptr);

	set_left_join(&ptr);

	PUT_HORIZONTAL_LINES(ptr);

	set_rem_unbroken(&ptr,
			 res_y - 1lu,
			 set_center_join,
			 set_right_join);

	*dbl_ptr = ptr;
}

/* unbroken line (top, mid, or bot) */
void set_line_with_token(char **dbl_ptr,
			 const size_t res_y,
			 const size_t token_y,
			 void (*token_setter)(char **),
			 struct JoinSetters *join_setters)
{
	char *ptr = *dbl_ptr;

	void (*set_left_join)(char **)	 = join_setters->left;
	void (*set_center_join)(char **) = join_setters->center;
	void (*set_right_join)(char **)  = join_setters->right;

	PUT_ANSI_WHITE_BG(ptr);

	set_left_join(&ptr);

	if (token_y == 0lu) {


	}

SET_REM_UNBROKEN:

UPDATE_DBL_PTR_AND_RETURN:
	*dbl_ptr = ptr;
}

/* remaining unbroken line (top, mid, or bot) */
void set_rem_unbroken(char **dbl_ptr,
		      const size_t rem_y,
		      void (*set_center_join)(char **),
		      void (*set_right_join)(char **))
{
	char *ptr = *dbl_ptr;

	for (size_t y = 0lu; y < rem_y; ++y) {

		set_center_join(&ptr);

		PUT_HORIZONTAL_LINES(ptr);
	}

	set_right_join(&ptr);

	PUT_ANSI_RESET(ptr);

	PUT_CHAR(ptr, '\n');

	*dbl_ptr = ptr;
}



/* COST TOKEN SETTER FUNCTIONS
 ******************************************************************************/

void set_cost_token_0(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_FAINT(ptr);
	PUT_SPACE(ptr);

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
