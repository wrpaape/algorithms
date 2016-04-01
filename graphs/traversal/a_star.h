#ifndef GRAPHS_TRAVERSAL_A_STAR_H
#include <time.h>

/* enum AStarNodePosition { */
/* 	GOAL, */
/* 	HORZ, */
/* 	VERT */
/* }; */

/* enum AStarNodeType { */
/* 	INNER, */
/* 	MIN_BOUND, */
/* 	MAX_BOUND */
/* }; */


struct AStarConstants {
	const int min_cost;
	const double w_cost;
	const double w_prox;
	struct Coords *lims;
	struct Coords *goal;
};

struct AStarNode {
	int cost;
	size_t prox;
	double score;
	struct Coords *coords;
	struct AStarNode *next;
};

struct AStarBranch {
	struct AStarNode *head;
	struct AStarNode *last;
}


struct AStarResults {
	size_t min_step_count;
	size_t best_step_count;
	size_t branch_count;
	int total_cost;
	clock_t time_elapsed;
	struct Coords *start;
	struct AStarBranch *best;
};

struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts);

void init_a_star_constants(struct AStarConstants *CONSTS,
			   struct Bounds *cost,
			   struct Coords *goal,
			   const size_t x_max,
			   const size_t y_max);

void report_a_star_results(struct AStarResults *results);

void a_star_node_to_string(char *buffer, const void *vstep);

static inline size_t calc_prox(struct Coords *c0,
			       struct Coords *c1);


inline void free_a_star_results(struct AStarResults *results)
{
	free(results->best);
	free(results);
}
#define GRAPHS_TRAVERSAL_A_STAR_H
#endif /* ifndef GRAPHS_TRAVERSAL_A_STAR_H */
