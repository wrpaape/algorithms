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

	sprintf(buffer, "  {\n"
			"    x:     %zu,\n"
			"    y:     %zu,\n"
			"    cost:  %d,\n"
			"    prox:  %zu,\n"
			"    score: %f\n"
			"  }\n",
		node->x, node->y, node->cost, node->prox, node->score);
}


struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts)
{
	/* unpack cost map and enpoints */
	const size_t min_cost = map->act->min;
	const size_t max_cost = map->act->max;

	const size_t x_start = pts->start->x;
	const size_t y_start = pts->start->y;

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
		.costs	    = map->costs,
		.min_cost   = min_cost,
		.w_cost	    = COST_BIAS / ((double) (max_cost - min_cost)),
		.w_prox	    = PROX_BIAS / ((double) max_prox),
		.x_max_cost = map->res->x - 1lu,
		.y_max_cost = y_max_horz,
		.x_goal	    = x_goal,
		.y_goal	    = y_goal,
		.x_max_horz = x_max_horz,
		.y_max_horz = y_max_horz,
		.x_max_vert = x_max_vert,
		.y_max_vert = y_max_vert
	};

	/* initialize lookup table of successor generator functions, 'gen_map' */
	const size_t count_rows	  = x_max_horz + 1lu;
	const size_t count_horz_y = y_max_vert;
	const size_t count_vert_y = y_max_vert + 1lu;

	const size_t horz_row_bytes = sizeof(AdjacentsGenFun) * count_horz_y;
	const size_t vert_row_bytes = sizeof(AdjacentsGenFun) * count_vert_y;

	AdjacentsGenFun **gen_map;
	AdjacentsGenFun *gen_row;

	size_t x, y;

	HANDLE_MALLOC(gen_map, sizeof(AdjacentsGenFun *) * count_rows);

	/* set first row of horizontal nodes to min bounds */
	HANDLE_MALLOC(gen_row, horz_row_bytes);
	gen_map[0lu] = gen_row;

	for (y = 0lu; y < count_horz_y; ++y)
		gen_row[y] = &generate_adjacents_MIN_BOUND_HORZ;


	/* fill inner nodes */
	x = 1lu;

	while (1) {
		/* set first and last cells of vert row to bounds */
		HANDLE_MALLOC(gen_row, vert_row_bytes);
		gen_map[x] = gen_row;

		gen_row[0lu] = &generate_adjacents_MIN_BOUND_VERT;

		for (y = 1lu; y < y_max_vert; ++y)
			gen_row[y] = &generate_adjacents_INNER_VERT;

		gen_row[y_max_vert] = &generate_adjacents_MAX_BOUND_VERT;

		if (x == x_max_vert)
			break;

		/* set inner row of horz cells */
		++x;
		HANDLE_MALLOC(gen_row, horz_row_bytes);
		gen_map[x] = gen_row;

		for (y = 0lu; y < count_horz_y; ++y)
			gen_row[y] = &generate_adjacents_INNER_HORZ;

		++x;
	}

	/* set last row of horizontal nodes to max bounds */
	HANDLE_MALLOC(gen_row, horz_row_bytes);
	gen_map[x_max_horz] = gen_row;

	for (y = 0lu; y < count_horz_y; ++y)
		gen_row[y] = generate_adjacents_MAX_BOUND_HORZ;


	/* initialize root noode */
	struct AStarNode *root = init_a_star_node(x_start,
						  y_start,
						  0,
						  NULL,
						  &CONST);

	/* initialize priority list of open successor nodes sorted
	 * according to 'best_successor' */
	struct BHeap *successors = init_bheap(&best_successor);

	/* initialize state accumulator */
	struct AStarState STATE = {
		.successors   = successors,
		.path	      = root,
		.gen_map      = gen_map,
		.branch_count = 1lu
	};

	/* look up root node generator */
	AdjacentsGenFun root_gen = gen_map[x_start][y_start];

	/* close generator for root node */
	gen_map[x_start][y_start] = NULL;

	printf("x_start: %zu\ny_start: %zu\n", x_start, y_start);
	printf("x_goal:  %zu\ny_goal:  %zu\n", x_goal,  y_goal);


	/* generate first round of successors, inserting them into
	 * 'successors' */
	root_gen(successors, &CONST, x_start, y_start);


	/* begin pathfinding */

	clock_t time_start = clock();

	find_best_path(&STATE, &CONST);

	clock_t time_finish = clock();

	/* build and return results accumulator */
	return a_star_build_results(&STATE, &CONST, time_start, time_finish);
}

void find_best_path(struct AStarState *STATE,
		    struct AStarConst *CONST)
{

	/* update STATE
	 * ================================================================== */

	/* pop next successor, 'node' from 'successors' */
	struct AStarNode *node = bheap_extract(STATE->successors);

	/* append 'node' to 'path' */
	node->prev = STATE->path;
	STATE->path->next = node;
	STATE->path = node;


	/* if proximity to goal is zero... */
	if (node->prox == 0lu) {

		node->next = NULL; /* terminate 'path' */

		return;
	}

	/* otherwise increment 'branch_count' */
	++(STATE->branch_count);

	char buff[300];


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

	results->time_elapsed = time_finish - time_start;

	return NULL;
}

struct AStarNode *init_a_star_node(const size_t x,
				   const size_t y,
				   const int cost,
				   struct AStarNode *parent,
				   struct AStarConst *CONST)
{
	const size_t prox = calc_prox(x, y, CONST->x_goal, CONST->y_goal);

	const double score = ((cost * CONST->w_cost) + CONST->min_cost)
			   +  (prox * CONST->w_prox);


	struct AStarNode *node;

	HANDLE_MALLOC(node, sizeof(struct AStarNode));

	node->x	    = x;
	node->y	    = y;
	node->prox  = prox;
	node->cost  = cost;
	node->score = score;
	node->prev  = parent;

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

/* successor generators
 * ========================================================================== */
void generate_adjacents_MIN_BOUND_HORZ(struct AStarAdjsBuff *buffer,
				       struct AStarNode *parent,
				       struct AStarConst *Const)
{

	buffer->count = 3lu;
	const size_t y_parent = parent->y;
	const size_t x_above = 0lu;
	const size_t x_upper = 1lu;
	const size_t x_ceil  = 2lu;
	const size_t y_upper = y + 1lu;
	const int cost_above = CONST->costs[x_above][y];

	/* insert upper sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_ceil,  y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_upper, cost_above, CONST));
}

void generate_adjacents_MAX_BOUND_HORZ(struct BHeap *successors,
					struct AStarConst *CONST,
					const size_t x,
					const size_t y)
{

	const size_t x_below = CONST->x_max_cost;
	const size_t x_lower = x - 1lu;
	const size_t x_floor = x - 2lu;
	const size_t y_upper = y + 1lu;
	const int cost_below = CONST->costs[x_below][y];

	/* insert lower sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_floor, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_upper, cost_below, CONST));
}

void generate_adjacents_INNER_HORZ(struct BHeap *successors,
				    struct AStarConst *CONST,
				    const size_t x,
				    const size_t y)
{
	const size_t x_above = x / 2lu;
	const size_t x_below = x_above - 1lu;
	const size_t x_ceil  = x + 2lu;
	const size_t x_upper = x + 1lu;
	const size_t x_lower = x - 1lu;
	const size_t x_floor = x - 2lu;
	const size_t y_upper = y + 1lu;
	const int cost_above = CONST->costs[x_above][y];
	const int cost_below = CONST->costs[x_below][y];

	/* insert upper sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_ceil,  y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_upper, cost_above, CONST));

	/* insert lower sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_floor, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_upper, cost_below, CONST));
}

void generate_adjacents_MIN_BOUND_VERT(struct BHeap *successors,
					struct AStarConst *CONST,
					const size_t x,
					const size_t y)
{

	const size_t x_level = x / 2lu;
	const size_t x_upper = x + 1lu;
	const size_t x_lower = x - 1lu;
	const size_t y_right = 0lu;
	const size_t y_ceil  = 1lu;
	const int cost_right = CONST->costs[x_level][y_right];

	/* insert right-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(x,       y_ceil,	cost_right, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_right,	cost_right, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_right, cost_right, CONST));
}

void generate_adjacents_MAX_BOUND_VERT(struct BHeap *successors,
					struct AStarConst *CONST,
					const size_t x,
					const size_t y)
{

	const size_t x_level = x / 2lu;
	const size_t x_upper = x + 1lu;
	const size_t x_lower = x - 1lu;
	const size_t y_left  = CONST->y_max_cost;
	const size_t y_floor = y_left - 1lu;
	const int cost_left  = CONST->costs[x_level][y_left];

	/* insert left-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(x,       y_floor,	cost_left, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_left,	cost_left, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_left,	cost_left, CONST));
}

void generate_adjacents_INNER_VERT(struct BHeap *successors,
				   struct AStarConst *CONST,
				   const size_t x,
				   const size_t y)
{
	const size_t x_level = x / 2lu;
	const size_t x_upper = x + 1lu;
	const size_t x_lower = x - 1lu;
	const size_t y_ceil  = y + 1lu;
	const size_t y_right = y;
	const size_t y_left  = y - 1lu;
	const size_t y_floor = y - 2lu;
	const int cost_left  = CONST->costs[x_level][y_left];
	const int cost_right = CONST->costs[x_level][y_right];

	/* insert right-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(x,       y_ceil,	cost_right, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_right,	cost_right, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_right, cost_right, CONST));

	/* insert left-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(x,       y_floor,	cost_left, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_left,	cost_left, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_left,	cost_left, CONST));
}
