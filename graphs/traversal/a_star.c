#include "utils/utils.h"
#include "bheap.h"
#include "maps/maker.h"
#include "maps/paths.h"
#include "traversal/a_star.h"

#define COST_BIAS 1.0
#define PROX_BIAS 1.0

extern inline void free_a_star_results(struct AStarResults *results);

int best_a_star_step_node(const void *vstep1, const void *vstep2)
{
	struct AStarStep *step1 = (struct AStarStep *) vstep1;
	struct AStarStep *step2 = (struct AStarStep *) vstep2;


	return step1->weight < step2->weight;
}

void a_star_step_node_to_string(char *buffer, const void *vstep)
{
	struct AStarStepNode *step = (struct AStarStepNode *) vstep;

	sprintf(buffer, "  {"
			"\n    cost:   %d,"
			"\n    prox:   %zu,"
			"\n    weight: %f"
			"\n  }",
		step->cost, step->prox, step->weight);
}


struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts)
{
	/* unpack map info */
	struct *horiz = pts->horiz;
	struct *vert  = pts->vert;

	/* initialize 'DEAD' table, (set all to live) */
	bool DEAD[horiz->x][vert->y] = { { false } };



	/* initialize accumulator */
	struct AStarAcc acc = {
		.cost  = 0,
		.steps = 0,
		.head
	}

	clock_t time_start  = clock();



	clock_t time_finish = clock();

	struct AStarResults *results;

	HANDLE_MALLOC(results, sizeof(struct AStarResults));

	results->jjjjjjj

	return;
}



void report_a_star_results(struct AStarResults *results)
{
	struct AStarAcc *best      = results->best;
	struct AStarPathNode *path = best->head;

	size_t prev_x = path->coords->x;
	size_t prev_y = path->coords->y;

	size_t next_x, next_y;
	char *dir;


	while (1) {

		next_x = path->coords->x;
		next_y = path->coords->y;

		if (next_x > prev_x)
			dir = " DOWN ";

		else if(next_x < prev_x)
			dir = "  UP  ";

		else if(next_y > prev_x)
			dir = "RIGHT ";

		else
			dir = " LEFT ";

		printf("(%zu, %zu) %s to (%zu, %zu) at a cost of %d\n",
		       prev_x, prev_y, dir, next_x, next_y, path->step->cost);

		path = path->next;

		if (path == NULL)
			break;

		prev_x = next_x;
		prev_y = next_y;
	}




	printf("\n\n"
	       "total cost:     %d\n"
	       "steps taken:    %zu\n"
	       "least steps:    %zu\n"
	       "count explored: %zu\n"
	       "time elapsed:   %llu\n",
	       best->cost,
	       best->steps,
	       results->least_steps,
	       results->count_explored,
	       results->time_elapsed);
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
