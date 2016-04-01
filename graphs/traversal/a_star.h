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


struct AStarConst {
	const int min_cost;
	const double w_cost;
	const double w_prox;
	const size_t x_goal;
	const size_t y_goal;
	const size_t x_max_horz;
	const size_t y_max_horz;
	const size_t x_max_vert;
	const size_t y_max_vert;
};


struct AStarNode {
	size_t x;
	size_t y;
	size_t prox;
	int cost;
	double score;
	struct AStarNode *prev;
	struct AStarNode *next;
};

struct AStarState {
	struct BHeap *successors;
	struct AStarNode *path;
	bool **closed;
	size_t branch_count;
};


struct AStarResults {
	size_t min_step_count;
	size_t best_step_count;
	size_t branch_count;
	int total_cost;
	clock_t time_elapsed;
	struct AStarNode *path;
};

struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts);

void a_star_do_next(struct AStarState *STATE,
		    struct AStarConst *CONST);

struct AStarResults *a_star_build_results(struct AStarState *STATE,
					  struct AStarConst *CONST,
					  clock_t time_start,
					  clock_t time_finish);

void init_a_star_constants(struct AStarConst *CONST,
			   struct Bounds *cost,
			   struct Coords *goal,
			   const size_t x_max,
			   const size_t y_max);

void report_a_star_results(struct AStarResults *results);

void a_star_node_to_string(char *buffer, const void *vstep);

inline size_t calc_prox(const size_t x0, const size_t y0,
			const size_t x1, const size_t y1);


inline void free_a_star_results(struct AStarResults *results);
{
	for (struct AStarNode *node = results->path->next;
	     node != NULL;
	     free(node->prev), node = node->next);

	free(results);
}
#define GRAPHS_TRAVERSAL_A_STAR_H
#endif /* ifndef GRAPHS_TRAVERSAL_A_STAR_H */
