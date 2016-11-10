#include "usa.h"

static struct Node nodes_map[50];
static unsigned int distances_map[50][50];
char *restrict distances_buffer;
static bool stop;
static int total_distance;

static inline void
get_distance_row(unsigned int *restrict distance,
		 unsigned int *const restrict distance_until,
		 const char *restrict *const restrict buffer_ptr)
{
	const char *restrict failure;

	do {
		if (UNLIKELY(!get_uint(distance,
				       buffer_ptr,
				       &failure))) {
			free(distances_buffer);
			exit_on_failure(failure);
		}

		++(*buffer_ptr); /* skip ',' */
		++distance;
	} while (distance < distance_until);
}


static inline void
path_init(struct Path *const restrict path,
	  const unsigned int *const restrict self,
	  const unsigned int next)
{
	path->self     = self;
	path->next     = next;
	path->distance = self[next];
}


static inline void
init_nodes_distances_maps(void)
{
	unsigned int next;
	unsigned int *restrict row;
	unsigned int *restrict next_row;
	struct Node *restrict node;
	char *restrict buffer;
	const char *restrict failure;

	if (UNLIKELY(!read_file(&distances_buffer,
				DISTANCES_PATH,
				&failure)))
	    exit_on_failure(failure);



	buffer	 = distances_buffer;
	node	 = &nodes_map[0];
	row	 = &distances_map[0][0];
	next_row = row + 50;
	next	 = 1u;

	do {
		get_location(&node->location,
			     &buffer);

		get_distance_row(row,
				 next_row,
				 (const char **) &buffer);

		path_init(&node->path,
			  row,
			  next);

		++node;
		row = next_row;
		next_row += 50;
		++next;
	} while (next < 50);

	next = 0;

	get_location(&node->location,
		     &buffer);

	get_distance_row(row,
			 next_row,
			 (const char **) &buffer);

	path_init(&node->path,
		  row,
		  next);
}

static inline void
put_path(const struct Node *const restrict node1,
	 const struct Node *const restrict node2,
	 char *restrict *const restrict buffer_ptr)
{
	char *restrict buffer;

	buffer = *buffer_ptr;

	put_location(&buffer,
		     &node1->location);

	*buffer = ' '; ++buffer;
	*buffer = 't'; ++buffer;
	*buffer = 'o'; ++buffer;
	*buffer = ' '; ++buffer;

	put_location(&buffer,
		     &node2->location);

	*buffer = ':'; ++buffer;
	*buffer = ' '; ++buffer;

	put_uint(&buffer,
		 node2->path.distance);

	*buffer = ' ';	++buffer;
	*buffer = 'k';	++buffer;
	*buffer = 'm';	++buffer;
	*buffer = '\n'; ++buffer;

	*buffer_ptr = buffer;
}

static inline void
write_solution(void)
{
	const struct Node *restrict node;
	const struct Node *restrict next_node;
	char *restrict ptr;
	const char *restrict failure;
	static char buffer[PATH_BUFFER_SIZE];


	const struct Node *const restrict first_node = &nodes_map[0];

	node	  = first_node;
	next_node = &nodes_map[node->path.next];
	ptr	  = &buffer[0];

	while (1) {
		put_path(node,
			 next_node,
			 &ptr);

		if (next_node == first_node)
			break;

		node	  = next_node;
		next_node = &nodes_map[node->path.next];
	}

	if (UNLIKELY(!write_file(&buffer[0],
				 ptr - &buffer[0],
				 SOLUTION_PATH,
				 &failure))) {
		free(distances_buffer);
		exit_on_failure(failure);
	}
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
	init_nodes_distances_maps();
	write_solution();

	return 0;
}

