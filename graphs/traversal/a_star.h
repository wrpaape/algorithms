#ifndef GRAPHS_TRAVERSAL_A_STAR_H
#include <time.h>

enum NodeType {
	GOAL
	INNER_VERT,
	INNER_HORZ,
	BOUND_VERT_MIN,
	BOUND_VERT_MAX,
	BOUND_HORZ_MIN,
	BOUND_HORZ_MAX
};

struct AStarWeights {
	const int min_cost;
	const double w_cost;
	const double w_prox;
};

struct AStarNode {
	enum NodeType;
	struct Coords *coords;
	struct AStarStep *next_step;
};

struct AStarStep {
	int cost;
	size_t prox;
	double weight;
	struct AStarNode *next_node;
};


struct AStarResults {
	struct AStarStep *head;
	struct AStarStep *last;
	size_t branch_count;
	size_t best_step_count;
	size_t min_step_count;
	int total_cost;
	clock_t time_elapsed;
};

struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts);


void report_a_star_results(struct AStarResults *results);
void a_star_step_node_to_string(char *buffer, const void *vstep);

/* static inline size_t calc_max_prox(struct AStarPathBounds *BOUNDARIES) */

/* static inline size_t calc_max_prox(const size_t max_x,  const size_t max_y, */
/* 				   const size_t goal_x, const size_t goal_y); */

/* static inline void calc_prox(const size_t x0, const size_t y0, */
/* 			     const size_t x1, const size_t y1); */

inline void free_a_star_results(struct AStarResults *results)
{
	free(results->best);
	free(results);
}
#define GRAPHS_TRAVERSAL_A_STAR_H
#endif /* ifndef GRAPHS_TRAVERSAL_A_STAR_H */
