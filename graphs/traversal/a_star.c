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

void a_star_node_to_string(char *buffer, const void *vstep)
{
	struct AStarNode *node = (struct AStarNode *) vstep;

	sprintf(buffer, "  {"
			"\n    cost:  %zu,"
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


	struct AStarConstants CONSTS = {
		.min_cost   = min_cost;
		.w_cost	    = COST_BIAS / ((double) (max_cost - min_cost));
		.w_prox	    = PROX_BIAS / ((double) max_prox);
		.x_goal	    = x_goal;
		.y_goal	    = y_goal;
		.x_max_horz = x_max_horz;
		.y_max_horz = y_max_horz;
		.x_max_vert = x_max_vert;
		.y_max_vert = y_max_vert;
	};



	/* initialize priority list of open successor nodes sorted
	 * according to 'best_successor' */
	struct BHeap *successors = init_bheap(best_successor);

	/* initialize root node and insert into successors */

	struct AStarNode *root = init_a_star_node(x_start,
						  y_start,
						  0,
						  NULL,
						  &CONSTS);
	bheap_insert(successors, root);


	/* initialize 'CLOSED' coordinates table, (set all to open) */
	bool CLOSED[x_max_horiz + 1lu][y_max_vert + 1lu] = { { false } };

	/* initialize state accumulator */
	struct AStarState STATE

	/* 'close' starting coordinates and set first generation successors */

	clock_t time_start = clock();

	a_star_do_next(successors, , &CONSTS, x_start, y_start);

	clock_t time_finish = clock();



	/* initialize results accumulator */
	struct AStarResults *results;

	HANDLE_MALLOC(results, sizeof(struct AStarResults));


	return NULL;
}

struct AStarNode *init_a_star_node(const size_t x,
				   const size_t y,
				   const int cost,
				   struct AStarNode *prev,
				   struct AStarConstants *CONSTS)
{
	const size_t prox  = calc_prox(x, y, CONSTS->x_goal, CONSTS->y_goal);

	const double score = ((cost * CONSTS->w_cost) + CONSTS->min_cost)
			   +  (prox * CONSTS->w_prox);


	struct AStarNode *node;

	HANDLE_MALLOC(node, sizeof(struct AStarNode));

	node->x	    = x;
	node->y	    = y;
	node->prox  = prox;
	node->cost  = cost;
	node->score = score;
	node->prev  = prev;

	return node;
}

inline size_t calc_prox(const size_t x0, const size_t y0,
			const size_t x1, const size_t y1)
{
	return (x1 > x0 ? (x1 - x0) : (x0 - x1))
	       (y1 > y0 ? (y1 - y0) : (y0 - y1));
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
