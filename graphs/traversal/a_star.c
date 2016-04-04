#include "utils/utils.h"
#include "bheap.h"
#include "maps/maker.h"
#include "maps/paths.h"
#include "traversal/a_star.h"

#define COST_BIAS 1.0
#define PROX_BIAS 1.0

extern inline void free_a_star_results(struct AStarResults *results);

int best_successor(const void *vnode1, const void *vnode2)
{
	struct AStarNode *node1 = (struct AStarNode *) vnode1;
	struct AStarNode *node2 = (struct AStarNode *) vnode2;


	return node1->score < node2->score;
}

void a_star_node_to_string(char *buffer, const void *vnode)
{
	struct AStarNode *node = (struct AStarNode *) vnode;

	sprintf(buffer, "  {"
			"\n    cost:  %d,"
			"\n    prox:  %zu,"
			"\n    score: %f"
			"\n  }",
		node->cost, node->prox, node->score);
}


struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts)
{
	/* unpack cost map and enpoints */

	int **costs = map->costs;

	const size_t min_cost = map->act->min;
	const size_t max_cost = map->act->max;

	const size_t x_start = pts->goal->x;
	const size_t y_start = pts->goal->y;

	const size_t x_goal = pts->goal->x;
	const size_t y_goal = pts->goal->y;

	const size_t x_max_horz = pts->horz->x;
	const size_t y_max_horz = pts->horz->y;

	const size_t x_max_vert = pts->vert->x;
	const size_t y_max_vert = pts->vert->y;


	/* initialize weights for determining heuristic, other constants */
	const size_t g_to_x_max = x_max_horz - x_goal;
	const size_t g_to_y_max = y_max_vert - y_goal;

	/* calculate furthest distance from goal within map bounds */
	const size_t max_prox = (g_to_x_max > x_goal ? g_to_x_max : x_goal)
			      + (g_to_y_max > y_goal ? g_to_y_max : y_goal);


	struct AStarConst CONST = {
		.min_cost   = min_cost,
		.w_cost	    = COST_BIAS / ((double) (max_cost - min_cost)),
		.w_prox	    = PROX_BIAS / ((double) max_prox),
		.x_goal	    = x_goal,
		.y_goal	    = y_goal,
		.x_max_horz = x_max_horz,
		.y_max_horz = y_max_horz,
		.x_max_vert = x_max_vert,
		.y_max_vert = y_max_vert
	};

	/* initialize priority list of open successor nodes sorted
	 * according to 'best_successor' */
	struct BHeap *successors = init_bheap(best_successor);

	/* initialize root node and insert into successors */

	struct AStarNode *root = init_a_star_node(x_start,
						  y_start,
						  0,
						  &CONST);
	bheap_insert(successors, root);

	/* initialize lookup table of node types, 'node_map', (set all to open) */

	const size_t count_rows = x_max_horz + 1lu;
	const size_t count_horz_y = y_max_vert;
	const size_t count_vert_y = y_max_vert + 1lu;

	const size_t horz_row_bytes = sizeof(enum AStarNodeType) * count_horz_y;
	const size_t vert_row_bytes = sizeof(enum AStarNodeType) * count_vert_y;

	enum AStarNodeType **type_map;
	enum AStarNodeType *type_row;

	size_t x, y;


	HANDLE_MALLOC(type_map,
		      sizeof(enum AStarNodeType *) * count_rows);

	/* set first row of horizontal nodes to min bounds */
	type_row = type_map[0lu];
	HANDLE_MALLOC(type_row, horz_row_bytes);

	for (y = 0lu; y < count_horz_y; ++y)
		type_row[y] = MIN_BOUND_HORZ;


	/* fill inner nodes */
	x = 1lu;

	while (1) {
		/* set first and last cells of vert row to bounds */
		type_row = type_map[x];
		HANDLE_MALLOC(type_row, vert_row_bytes);

		type_row[0lu]	     = MIN_BOUND_VERT;
		type_row[y_max_vert] = MAX_BOUND_VERT;

		for (y = 1lu; y < y_max_vert; ++y)
			type_row[y] = INNER_VERT;

		if (x == x_max_vert)
			break;

		/* set inner row of horz cells */
		++x;
		type_row = type_map[x];
		HANDLE_MALLOC(type_row, horz_row_bytes);

		for (y = 0lu; y < count_horz_y; ++y)
			type_row[y] = INNER_HORZ;

		++x;
	}

	/* set last row of horizontal nodes to max bounds */
	type_row = type_map[x_max_horz];
	HANDLE_MALLOC(type_row, horz_row_bytes);

	for (y = 0lu; y < count_horz_y; ++y)
		type_row[y] = MAX_BOUND_HORZ;

	/* set goal coordinates */
	type_map[x_goal][y_goal] = GOAL;


	/* initialize state accumulator */
	struct AStarState STATE = {
		.successors   = successors,
		.path	      = NULL,
		.type_map     = type_map,
		.branch_count = 0
	};

	/* begin pathfinding */

	clock_t time_start = clock();

	a_star_do_next(&STATE, &CONST);

	clock_t time_finish = clock();

	/* build and return results accumulator */
	return a_star_build_results(&STATE, &CONST, time_start, time_finish);
}

void a_star_do_next(struct AStarState *STATE,
		    struct AStarConst *CONST)
{
	struct AStarNode *node = bheap_extract(STATE->successors);

	char buff[64];

	a_star_node_to_string(buff, node);

	puts(buff);
}

struct AStarResults *a_star_build_results(struct AStarState *STATE,
					  struct AStarConst *CONST,
					  clock_t time_start,
					  clock_t time_finish)
{
	struct AStarResults *results;

	HANDLE_MALLOC(results, sizeof(struct AStarResults));

	return NULL;
}

struct AStarNode *init_a_star_node(const size_t x,
				   const size_t y,
				   const int cost,
				   struct AStarConst *CONST)
{
	const size_t prox  = calc_prox(x, y, CONST->x_goal, CONST->y_goal);

	const double score = ((cost * CONST->w_cost) + CONST->min_cost)
			   +  (prox * CONST->w_prox);


	struct AStarNode *node;

	HANDLE_MALLOC(node, sizeof(struct AStarNode));

	node->x	    = x;
	node->y	    = y;
	node->prox  = prox;
	node->cost  = cost;
	node->score = score;

	return node;
}

inline size_t calc_prox(const size_t x0, const size_t y0,
			const size_t x1, const size_t y1)
{
	return (x1 > x0 ? (x1 - x0) : (x0 - x1))
	     + (y1 > y0 ? (y1 - y0) : (y0 - y1));
}

void report_a_star_results(struct AStarResults *results)
{
	puts("YOLO");
	/* struct AStarNode *node = results->best->head; */

	/* size_t x_prev = results->x_start; */
	/* size_t y_prev = results->y_start; */

	/* size_t x_next, y_next; */
	/* char *dir; */


	/* while (1) { */
	/* 	x_next = node->x; */
	/* 	y_next = node->y; */

	/* 	if (x_next > x_prev) */
	/* 		dir = " DOWN "; */

	/* 	else if(x_next < x_prev) */
	/* 		dir = "  UP  "; */

	/* 	else if(y_next > x_prev) */
	/* 		dir = "RIGHT "; */

	/* 	else */
	/* 		dir = " LEFT "; */

	/* 	printf("(%zu, %zu) %s to (%zu, %zu) at a cost of %d\n", */
	/* 	       x_prev, y_prev, dir, x_next, y_next, node->cost); */

	/* 	node = node->next; */

	/* 	if (node == NULL) */
	/* 		break; */

	/* 	x_prev = x_next; */
	/* 	y_prev = y_next; */
	/* } */




	/* printf("\n\n" */
	/*        "min steps to goal: %zu\n" */
	/*        "steps taken:       %zu\n" */
	/*        "total cost:        %d\n" */
	/*        "branches explored: %zu\n" */
	/*        "time elapsed:      %f s\n", */
	/*        results->min_step_count, */
	/*        results->best_step_count, */
	/*        best->total_cost, */
	/*        results->branch_count, */
	/*        ((double) results->time_elapsed) / (double) (CLOCKS_PER_SEC); */
}

/* inline size_t calc_max_prox(struct Coords *lims, */
/* 			    struct Coords *goal) */
/* { */
/* 	const size_t goal_max_dx = lims->x - goal->x; */
/* 	const size_t goal_max_dy = lims->y - goal->y; */

/* 	return (goal_max_dx > goal->x ? goal_max_dx : goal->x) */
/* 	     + (goal_max_dy > goal->y ? goal_max_dy : goal->y); */
/* } */

/* inline size_t calc_prox(struct Coords *c0, */
/* 			struct Coords *c1) */
/* { */
/* 	return (c1->x > c0->x ? (c1->x - c0->x) : (c0->x - c1->x) */
/* 	     + (c1->y > c0->y ? (c1->y - c0->y) : (c0->y - c1->y); */
/* } */
