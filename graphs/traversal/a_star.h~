#ifndef GRAPHS_TRAVERSAL_A_STAR_H
#include <time.h>

enum AStarNodeType {
	GOAL,
	CLOSED,
	INNER_HORZ,
	INNER_VERT,
	MIN_BOUND_HORZ,
	MIN_BOUND_VERT,
	MAX_BOUND_HORZ,
	MAX_BOUND_VERT
};


struct AStarConst {
	int **costs;
	const int min_cost;
	const double w_cost;
	const double w_prox;
	const size_t x_max_cost;
	const size_t y_max_cost;
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


typedef void (*SuccessorsGenFun)(struct BHeap *
				 struct AStarNode *,
				 struct AStarConst *,
				 const size_t,
				 const size_t);

void generate_successors_MIN_BOUND_HORZ(struct BHeap *successors,
					struct AStartNode *parent,
					struct AStarConst *CONST,
					const size_t x_parent,
					const size_t y_parent);

void generate_successors_MAX_BOUND_HORZ(struct BHeap *successors,
					struct AStartNode *parent,
					struct AStarConst *CONST,
					const size_t x_parent,
					const size_t y_parent);

void generate_successors_INNER_HORZ(struct BHeap *successors,
				    struct AStartNode *parent,
				    struct AStarConst *CONST,
				    const size_t x_parent,
				    const size_t y_parent);

void generate_successors_MIN_BOUND_VERT(struct BHeap *successors,
					struct AStartNode *parent,
					struct AStarConst *CONST,
					const size_t x_parent,
					const size_t y_parent);

void generate_successors_MAX_BOUND_VERT(struct BHeap *successors,
					struct AStartNode *parent,
					struct AStarConst *CONST,
					const size_t x_parent,
					const size_t y_parent);

void generate_successors_INNER_VERT(struct BHeap *successors,
				    struct AStartNode *parent,
				    struct AStarConst *CONST,
				    const size_t x_parent,
				    const size_t y_parent);


struct AStarState {
	struct BHeap *successors;
	struct AStarNode *path;
	size_t branch_count;
	SuccessorsGenFun **gen_map;
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

struct AStarNode *init_a_star_node(struct AStarConst *CONST,
				   struct AStarNode *parent,
				   const int cost,
				   const size_t x,
				   const size_t y);

struct AStarState {
	struct BHeap *successors;
	struct AStarNode *path;
	size_t branch_count;
	SuccessorsGenFun **gen_map;
};

void find_best_path(struct AStarState *STATE,
		    struct AStarConst *CONST);

struct AStarResults *a_star_build_results(struct AStarState *STATE,
					  struct AStarConst *CONST,
					  clock_t time_start,
					  clock_t time_finish);


void report_a_star_results(struct AStarResults *results);

void a_star_node_to_string(char *buffer, const void *vstep);

static inline size_t calc_prox(const size_t x0, const size_t y0,
			       const size_t x1, const size_t y1);


/* successor generators
 * ========================================================================== */
inline void generate_successors_MIN_BOUND_HORZ(struct AStarAdjsBuff *buffer,
					      struct AStarNode *parent,
					      struct AStarConst *Const)
{

	buffer->count = 3lu;
	const size_t y_parent = parent->y;
	const size_t x_above = 0lu;
	const size_t x_upper = 1lu;
	const size_t x_ceil  = 2lu;
	const size_t y_upper = y + 1lu;
	const int cost_above = CONST->costs[x_above][y];

	/* insert upper sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_ceil,  y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_upper, cost_above, CONST));
}

inline void generate_successors_MAX_BOUND_HORZ(struct BHeap *successors,
					struct AStarConst *CONST,
					const size_t x,
					const size_t y)
{

	const size_t x_below = CONST->x_max_cost;
	const size_t x_lower = x - 1lu;
	const size_t x_floor = x - 2lu;
	const size_t y_upper = y + 1lu;
	const int cost_below = CONST->costs[x_below][y];

	/* insert lower sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_floor, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_upper, cost_below, CONST));
}

inline void generate_successors_INNER_HORZ(struct BHeap *successors,
				    struct AStarConst *CONST,
				    const size_t x,
				    const size_t y)
{
	const size_t x_above = x / 2lu;
	const size_t x_below = x_above - 1lu;
	const size_t x_ceil  = x + 2lu;
	const size_t x_upper = x + 1lu;
	const size_t x_lower = x - 1lu;
	const size_t x_floor = x - 2lu;
	const size_t y_upper = y + 1lu;
	const int cost_above = CONST->costs[x_above][y];
	const int cost_below = CONST->costs[x_below][y];

	/* insert upper sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_ceil,  y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y,	cost_above, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_upper, cost_above, CONST));

	/* insert lower sucessors */
	bheap_insert(successors,
		     init_a_star_node(x_floor, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y,	cost_below, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_upper, cost_below, CONST));
}

inline void generate_successors_MIN_BOUND_VERT(struct BHeap *successors,
					struct AStarConst *CONST,
					const size_t x,
					const size_t y)
{

	const size_t x_level = x / 2lu;
	const size_t x_upper = x + 1lu;
	const size_t x_lower = x - 1lu;
	const size_t y_right = 0lu;
	const size_t y_ceil  = 1lu;
	const int cost_right = CONST->costs[x_level][y_right];

	/* insert right-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(x,       y_ceil,	cost_right, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_upper, y_right,	cost_right, CONST));
	bheap_insert(successors,
		     init_a_star_node(x_lower, y_right, cost_right, CONST));
}

void generate_successors_MAX_BOUND_VERT(struct BHeap *successors,
					struct AStartNode *parent,
					struct AStarConst *CONST,
					const size_t x_parent,
					const size_t y_parent)
{

	const size_t x_level = x_parent / 2lu;
	const size_t x_upper = x_parent + 1lu;
	const size_t x_lower = x_parent - 1lu;
	const size_t y_left  = CONST->y_max_cost;
	const size_t y_floor = y_left - 1lu;
	const int cost_left  = CONST->costs[x_level][y_left];

	/* insert left-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_left,
				      x_parent,
				      y_floor));
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_left,
				      x_upper,
				      y_left));
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_left,
				      x_lower,
				      y_left));
}

void generate_successors_INNER_VERT(struct BHeap *successors,
				    struct AStartNode *parent,
				    struct AStarConst *CONST,
				    const size_t x_parent,
				    const size_t y_parent)
{
	const size_t x_level = x_parent / 2lu;
	const size_t x_upper = x_parent + 1lu;
	const size_t x_lower = x_parent - 1lu;
	const size_t y_ceil  = y_parent + 1lu;
	const size_t y_right = y_parent;
	const size_t y_left  = y_parent - 1lu;
	const size_t y_floor = y_parent - 2lu;
	const int cost_left  = CONST->costs[x_level][y_left];
	const int cost_right = CONST->costs[x_level][y_right];

	/* insert right-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_right,
				      x_parent,
				      y_ceil));
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_right,
				      x_upper,
				      y_right));
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_right,
				      x_lower,
				      y_right));

	/* insert left-side sucessors */
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_left,
				      x_parent,
				      y_floor));
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_left,
				      x_upper,
				      y_left));
	bheap_insert(successors,
		     init_a_star_node(CONST,
				      parent,
				      cost_left,
				      x_lower,
				      y_left));
}

inline void free_a_star_results(struct AStarResults *results)
{
	for (struct AStarNode *node = results->path->next;
	     node != NULL;
	     free(node->prev), node = node->next);


	free(results);
}
#define GRAPHS_TRAVERSAL_A_STAR_H
#endif /* ifndef GRAPHS_TRAVERSAL_A_STAR_H */
