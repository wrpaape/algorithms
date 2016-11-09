#ifndef TSP_USA_USA_H_
#define TSP_USA_USA_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "usa/usa_utils.h"	/* struct Location, misc utils */


/* typedefs, struct definitions
 * ────────────────────────────────────────────────────────────────────────── */
struct Node;

struct Path {
	unsigned int *restrict self; /* can fit extra 4 bytes into Node free */
	unsigned int next;
	unsigned int distance;
};

struct Node {
	struct Path path;
	struct Location location;
};


static inline void
init_nodes_distances_maps(void);


#endif /* ifndef TSP_USA_USA_H_ */
