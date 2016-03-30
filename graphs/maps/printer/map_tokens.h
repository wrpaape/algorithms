#ifndef _GRAPHS_MAPS_PRINTER_MAP_TOKENS_H_
#define _GRAPHS_MAPS_PRINTER_MAP_TOKENS_H_
#include "utils/token.h"

#define MAX_COST_TOKEN_SIZE 13lu
#define START_TOKEN_SIZE 22lu
#define GOAL_TOKEN_SIZE 22lu
#define TOKEN_SPAN 8lu

struct JoinSetters {
	void (*left)(char **);
	void (*center)(char **);
	void (*right)(char **);
};

void set_cost_token_0(char **dbl_ptr);
void set_cost_token_1(char **dbl_ptr);
void set_cost_token_2(char **dbl_ptr);
void set_cost_token_3(char **dbl_ptr);
void set_cost_token_4(char **dbl_ptr);
void set_cost_token_5(char **dbl_ptr);
void set_cost_token_6(char **dbl_ptr);
void set_cost_token_7(char **dbl_ptr);
void set_cost_token_8(char **dbl_ptr);

static inline void set_cost_token(char **dbl_ptr,
				  const int cost,
				  const int min_cost,
				  const double token_ratio);

void set_unbroken_cost_row(char **dbl_ptr,
			   const size_t res_y,
			   const int min_cost,
			   const double token_ratio,
			   int *cost_row);

void set_rem_unbroken_cost_row(char **dbl_ptr,
			       size_t y,
			       const size_t res_y,
			       const int min_cost,
			       const double token_ratio,
			       int *cost_row);

void set_cost_row_with_token(char **dbl_ptr,
			     const size_t res_y,
			     const size_t token_y,
			     const int min_cost,
			     const double token_ratio,
			     void (*token_setter)(char **));


void set_top_left_join(char **dbl_ptr);
void set_top_center_join(char **dbl_ptr);
void set_top_right_join(char **dbl_ptr);

void set_mid_left_join(char **dbl_ptr);
void set_mid_center_join(char **dbl_ptr);
void set_mid_right_join(char **dbl_ptr);

void set_bot_left_join(char **dbl_ptr);
void set_bot_center_join(char **dbl_ptr);
void set_bot_right_join(char **dbl_ptr);

void set_unbroken_line(char **dbl_ptr,
		       const size_t res_y,
		       struct JoinSetters *join_setters);

void set_line_with_token(char **dbl_ptr,
			 const size_t res_y,
			 const size_t token_y,
			 void (*token_setter)(char **),
			 struct JoinSetters *join_setters);

void set_rem_unbroken_line(char **dbl_ptr,
			   const size_t rem_y,
			   void (*set_center_join)(char **),
			   void (*set_right_join)(char **));

struct JoinSetters TOP_LINE_JOIN_FUNS = {
	.left   = set_top_left_join;
	.center = set_top_center_join;
	.right  = set_top_right_join;
};

struct JoinSetters MID_LINE_JOIN_FUNS = {
	.left   = set_top_left_join;
	.center = set_top_center_join;
	.right  = set_top_right_join;
};

struct JoinSetters BOT_LINE_JOIN_FUNS = {
	.left   = set_top_left_join;
	.center = set_top_center_join;
	.right  = set_top_right_join;
};

/* BRIGHT BLACK_BG WHITE "◯" RESET
 * ◯ = <<226, 151, 139>> */
inline void set_start_token(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_BRIGHT(ptr);
	PUT_ANSI_BLACK_BG(ptr);
	PUT_ANSI_WHITE(ptr);
	PUT_CHAR(ptr, 226);
	PUT_CHAR(ptr, 151);
	PUT_CHAR(ptr, 139);

	*dbl_ptr = ptr;
}

/* BRIGHT BLACK_BG WHITE "╳" RESET
* ╳  = <<226, 149, 179>> */
inline void set_goal_token(char **dbl_ptr)
{
	char *ptr = *dbl_ptr;

	PUT_ANSI_BRIGHT(ptr);
	PUT_ANSI_BLACK_BG(ptr);
	PUT_ANSI_WHITE(ptr);
	PUT_CHAR(ptr, 226);
	PUT_CHAR(ptr, 149);

	*dbl_ptr = ptr;
}
#endif /* ifndef _GRAPHS_MAPS_PRINTER_MAP_TOKENS_H_ */
