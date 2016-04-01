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
			"\n    cost:   %zu,"
			"\n    prox:   %zu,"
			"\n    score: %f"
			"\n  }",
		node->cost, node->prox, node->score);
}


struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts)
{
	/* unpack map info */
	int **costs = map->costs;

	struct Coords *start = pts->start;
	struct Coords *goal  = pts->goal;
	struct Coords *horz  = pts->horz;
	struct Coords *vert  = pts->vert;

	const size_t x_max = horz->x;
	const size_t y_max = vert->y;


	/* initialize weights for determining heuristic, other constants */
	struct AStarConstants CONSTANTS;

	init_a_star_weights(&WEIGHTS, map->est, goal, x_max, y_max);

	/* initialize 'CLOSED' coordinates table, (set all to open) */
	bool CLOSED[x_max + 1lu][y_max + 1lu] = { { false } };

	/* initialize priority list of open successor nodes sorted
	 * according to 'best_successor' */
	struct BHeap *successors = init_bheap(best_successor);


	/* 'close' starting coordinates and set first generation successors */
	a_star_update_state(CLOSED, successors, start, WEIGHTS);




	/* initialize results accumulator */
	struct AStarResults *results;
	HANDLE_MALLOC(results, sizeof(struct AStarResults));


	results->head

	clock_t time_start = clock();
	clock_t time_finish = clock();

	return results;
}

a_star_update_state(bool **CLOSED,
		    struct BHeap *successors,
		    struct Coords *parent,
		    WEIGHTS);

	parent
	/* 'kill' starting coordinates */
	CLOSED[parent->x][start->y] = true;


void init_a_star_weights(struct AStarWeights *WEIGHTS,
			 struct Bounds *cost,
			 struct Coords *goal,
			 const size_t x_max,
			 const size_t y_max)
{

	const size_t g_to_x_max = x_max - goal->x;
	const size_t g_to_y_max = y_max - goal->y;

	const size_t max_prox = (g_to_x_max > goal->x ? g_to_x_max : goal->x)
			      + (g_to_y_max > goal->y ? g_to_y_max : goal->y);


	WEIGHTS->min_cost = cost->min;
	WEIGHTS->w_cost	  = COST_BIAS / ((double) (cost->max - cost->min));
	WEIGHTS->w_prox	  = PROX_BIAS / ((double) max_prox);
}

inline size_t calc_prox(struct Coords *c0,
			struct Coords *c1)
{
	return (c1->x > c0->x ? (c1->x - c0->x) : (c0->x - c1->x))
	     + (c1->y > c0->y ? (c1->y - c0->y) : (c0->y - c1->y));
}

void report_a_star_results(struct AStarResults *results)
{
	struct AStarNode *node = results->best->head;

	size_t prev_x = results->start->x;
	size_t prev_y = results->start->y;

	size_t next_x, next_y;
	char *dir;


	while (1) {

		next_x = node->coords->x;
		next_y = node->coords->y;

		if (next_x > prev_x)
			dir = " DOWN ";

		else if(next_x < prev_x)
			dir = "  UP  ";

		else if(next_y > prev_x)
			dir = "RIGHT ";

		else
			dir = " LEFT ";

		printf("(%zu, %zu) %s to (%zu, %zu) at a cost of %d\n",
		       prev_x, prev_y, dir, next_x, next_y, node->cost);

		node = node->next;

		if (node == NULL)
			break;

		prev_x = next_x;
		prev_y = next_y;
	}




	printf("\n\n"
	       "min steps to goal: %zu\n"
	       "steps taken:       %zu\n"
	       "total cost:        %d\n"
	       "branches explored: %zu\n"
	       "time elapsed:      %f s\n",
	       results->min_step_count,
	       results->best_step_count,
	       best->total_cost,
	       results->branch_count,
	       ((double) results->time_elapsed) / (double) (CLOCKS_PER_SEC);
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
