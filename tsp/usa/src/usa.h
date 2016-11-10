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


/* typedefs, struct definitions
 * ────────────────────────────────────────────────────────────────────────── */
struct Node;

struct Path {
	const unsigned int *restrict self; /* can fit +4 bytes into Node free */
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
	  const unsigned int *const restrict self,
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

static inline int
do_swap_path(struct Path *const restrict path,
	     const unsigned int next);

static inline int
swap_paths(struct Path *const restrict path1,
	   struct Path *const restrict path2);


#endif /* ifndef TSP_USA_USA_H_ */
