#ifndef GRAPHS_TRAVERSAL_A_STAR_H
#include <time.h>

struct AStarPathBounds {
	struct Coords *max;
	struct Coords *goal;
};

struct AStarWeights {
	const int min_cost;
	const double w_cost;
	const double w_prox;
};

struct AStarStepNode {
	double weight;
	/* ↓ for debugging purposes ↓ */
	int cost;
	size_t prox;
};

struct AStarPathNode {
	struct Coords *coords
	struct AStarStepNode *step;
	struct AStarPathNode *next;
};

struct AStarAcc {
	int cost;
	size_t steps_taken;
	struct AStarPathNode *last;
	struct AStarPathNode *head;
};

struct AStarResults {
	size_t least_steps;
	size_t count_explored;
	clock_t time_elapsed;
	struct AStarAcc *best;
};

struct AStarResults *a_star_least_cost_path(struct CostMap *map);

void set_a_star_weights(struct AStarWeights *WEIGHTS,
			const int min_cost,  const int max_cost
			const size_t max_x,  const size_t max_y,
			const size_t goal_x, const size_t goal_y);

void report_a_star_results(struct AStarResults *results);
void a_star_step_node_to_string(char *buffer, const void *vstep);

static inline size_t calc_max_prox(struct AStarPathBounds *BOUNDARIES);

static inline size_t calc_max_prox(const size_t max_x,  const size_t max_y,
				   const size_t goal_x, const size_t goal_y);

static inline void calc_prox(const size_t x0, const size_t y0,
			     const size_t x1, const size_t y1);

inline void free a_star_results(struct AStarResults *results)
{
	free(results->best);
	free(results);
}
#define GRAPHS_TRAVERSAL_A_STAR_H
#endif /* ifndef GRAPHS_TRAVERSAL_A_STAR_H */
