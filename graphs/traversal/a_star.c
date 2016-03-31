#include "utils/utils.h"
#include "bheap.h"
#include "maps/maker.h"
#include "traversal/a_star.h"

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

	const struct AStarWeights *WEIGHTS = calc_a_star_weights(res_x * 2lu,
								 res_y,
								 start_x,
								 start_y,
								 goal_x,
								 goal_y,
								 min_cost,
								 max_cost);
	const double COST_WEIGHT;
	const double PROX_WEIGHT;
}

struct AStarWeights *calc_a_star_weights(const size_t max_x,
					 const size_t max_y,
					 const size_t start_x,
					 const size_t start_y,
					 const size_t goal_x,
					 const size_t goal_y,
					 const int min_cost,
					 const int max_cost)
{
	const size_t goal_max_dx = max_x - goal_x;
	const size_t goal_max_dy = max_y - goal_y;

	/* max proximity to goal (min is zero) */
	const size_t max_prox = (goal_max_dx > goal_x ? goal_max_dx : goal_x)
			      + (goal_max_dy > goal_y ? goal_max_dy : goal_y);

	const size_t ini_prox = (start_x > goal_x ?
				   start_x - goal_x : goal_x - start_x)
				+ (start_y > goal_y ?
				   start_y - goal_y : goal_y - start_y);
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
	       "steps taken:    %zu\n"
	       "total cost:     %d\n"
	       "count explored: %zu\n"
	       "time elapsed:   %llu\n",
	       best->steps,
	       best->cost,
	       results->count_explored,
	       results->time_elapsed);
}
