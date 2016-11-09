#include "usa.h"

static struct Node nodes_map[50];
static unsigned int distances_map[50][50];
char *restrict distances_buffer;

static inline void
init_nodes_distances_maps(void)
{
}

static inline int
do_swap_path(struct Path *const restrict path,
	     const unsigned int next)
{
	const unsigned int new_distance = path->self[next];

	path->next = next;

	const int difference = new_distance - path->distance;

	path->distance = new_distance;

	return difference;
}

static inline int
swap_paths(struct Path *const restrict path1,
	   struct Path *const restrict path2)
{
	const unsigned int old_next1 = path1->next;

	return do_swap_path(path1,
			    path2->next)
	     + do_swap_path(path2,
			    old_next1);
}

int
main(void)
{
	return 0;
}

