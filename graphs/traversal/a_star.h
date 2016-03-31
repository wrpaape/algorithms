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
	int min_cost;
	double w_cost;
	double w_prox;
};

struct AStarNode {
	enum NodeType;
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
	struct AStarBranch *best;
	size_t branch_count;
	size_t best_step_count;
	size_t min_step_count;
	int total_cost;
	clock_t time_elapsed;
};

struct AStarResults *a_star_least_cost_path(struct CostMap *map,
					    struct Endpoints *pts);

void init_a_star_bias(struct AStarWeights *WEIGHTS,
		      struct Bounds *cost,
		      struct Coords *goal,
		      const size_t x_max,
		      const size_t y_max);

void report_a_star_results(struct AStarResults *results);

void a_star_node_to_string(char *buffer, const void *vstep);


inline void free_a_star_results(struct AStarResults *results)
{
	free(results->best);
	free(results);
}
#define GRAPHS_TRAVERSAL_A_STAR_H
#endif /* ifndef GRAPHS_TRAVERSAL_A_STAR_H */
