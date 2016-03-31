#ifndef GRAPHS_TRAVERSAL_A_STAR_H
#include <time.h>

struct AStarStepNode {
	int cost;
	size_t prox;
	double weight;
};

struct AStarPathNode {
	struct Coords *coords
	struct AStarStepNode *step;
	struct AStarPathNode *next;
};

struct AStarAcc {
	int cost;
	size_t steps;
	struct AStarPathNode *last;
	struct AStarPathNode *head;
};

struct AStarResults {
	size_t count_explored;
	clock_t time_elapsed;
	struct AStarAcc *best;
};

struct AStarResults *a_star_least_cost_path(struct CostMap *map);

void report_a_star_results(struct AStarResults *results);
void a_star_step_node_to_string(char *buffer, const void *vstep);

inline void free a_star_results(struct AStarResults *results)
{
	free(results->best);
	free(results);
}
#define GRAPHS_TRAVERSAL_A_STAR_H
#endif /* ifndef GRAPHS_TRAVERSAL_A_STAR_H */
