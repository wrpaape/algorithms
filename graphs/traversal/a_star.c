#include "utils/utils.h"
#include "bheap.h"
#include "maps/maker.h"
#include "traversal/a_star.h"

#define COST_BIAS 1.0
#define PROX_BIAS 1.0

extern inline void free a_star_results(struct AStarResults *results);

int best_a_star_step_node(const void *vstep1, const void *vstep2)
{
	struct AStarStepNode *step1 = (struct AStarStepNode *) vstep1;
	struct AStarStepNode *step2 = (struct AStarStepNode *) vstep2;


	return step1->weight < step2->weight;
}

void a_star_step_node_to_string(char *buffer, const void *vstep)
{
	struct AStarStepNode *step = (struct AStarStepNode *) vstep;

	sprintf(buffer, "  {"
			"\n    cost: %d,"
			"\n    prox: %zu,"
			"\n    weight: %f"
			"\n  }",
		step->cost, step->prox, step->weight);
}


struct AStarResults *a_star_least_cost_path(struct CostMap *map)
{
	/* unpack map info */
	const size_t res_x = map->res->x;
	const size_t res_y = map->res->y;

	const size_t start_x = map->start->x;
	const size_t start_y = map->start->y;

	const size_t goal_x = map->goal->x;
	const size_t goal_y = map->goal->y;

	const int min_cost = map->act->min;
	const int max_cost = map->act->max;

	int **costs = map->costs;

	/* set weights for comparing graph nodes */

	const size_t max_prox = calc_max_prox(res_x * 2lu, resy,
					      goal_x,      goal_y);
	const size_t goal_max_dx = max_x - goal_x;
	const size_t goal_max_dy = max_y - goal_y;

	struct AStarWeights WEIGHTS = {
		.min_cost = min_cost;
		.w_cost   = COST_BIAS / ((double) (max_cost - min_cost));
		.w_prox   = PROX_BIAS / ((double) max_prox);
	};

}

void set_a_star_weights(struct AStarWeights *WEIGHTS,
			const int min_cost,  const int max_cost
			const size_t max_x,  const size_t max_y,
			const size_t goal_x, const size_t goal_y)
{

	/* max proximity to goal (min is zero) */
	const size_t max_prox = (goal_max_dx > goal_x ? goal_max_dx : goal_x)
			      + (goal_max_dy > goal_y ? goal_max_dy : goal_y);


	memcpy(WEIGHTS, &weights, sizeof(struct AStarWeights));
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
	       best->steps_taken,
	       results->least_steps,
	       results->count_explored,
	       results->time_elapsed);
}






inline size_t calc_prox(const size_t x0, const size_t y0,
			const size_t x1, const size_t y1)
{
	return (x1 > x0 ? (x1 - x0) : (x0 - x1))
	     + (y1 > y0 ? (y1 - y0) : (y0 - y1));
}
