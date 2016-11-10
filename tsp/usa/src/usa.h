#ifndef TSP_USA_USA_H_
#define TSP_USA_USA_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "usa/usa_utils.h"		/* misc utils */
#include "random/random_utils.h"	/* random number generator */
#include "signal/signal_utils.h"	/* signal_report */


/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#define PATH_BUFFER_SIZE						\
(50 * ((2 * LOCATION_LENGTH) + DISTANCE_PATH_DIGITS_MAX + 9))

#define SOLUTION_BUFFER_SIZE						\
(PATH_BUFFER_SIZE + sizeof("\ntotal: km") + DISTANCE_TOTAL_DIGITS_MAX)

#define EXPONENT_CONSTANT	-1000
#define INITIAL_TEMPERATURE	1000000.0
#define DELTA_TEMPERATURE	0.1


/* typedefs, struct definitions
 * ────────────────────────────────────────────────────────────────────────── */
struct Path {
	const unsigned int *restrict edges;
	/* unsigned int self; */
	unsigned int next;
	unsigned int distance;
};

struct Node {
	struct Path path;
	const char *location;
};


void
catch_interrupt(int signal);

static inline void
get_distance_row(unsigned int *restrict distance,
		 unsigned int *const restrict distance_until,
		 const char *restrict *const restrict buffer_ptr);

static inline void
path_init(struct Path *const restrict path,
	  const unsigned int *const restrict edges,
	  const unsigned int self,
	  const unsigned int next);

static inline void
init_tsp_state(void);

static inline void
put_path(const struct Node *const restrict node1,
	 const struct Node *const restrict node2,
	 char *restrict *const restrict buffer_ptr);

static inline void
put_total(char *restrict *const restrict buffer_ptr);

static inline void
write_solution(void);

static inline void
sample_paths(struct Path *restrict *const restrict path1_ptr,
	     struct Path *restrict *const restrict path2_ptr);

static inline int
do_swap_path(struct Path *const restrict path,
	     const unsigned int next);

static inline int
swap_paths(struct Path *const restrict path1,
	   struct Path *const restrict path2);

static inline bool
make_inferior_transition(const int delta_distance,
			 const double temperature);

static inline void
evaluate(void);


#endif /* ifndef TSP_USA_USA_H_ */
