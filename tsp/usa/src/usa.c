#include "usa.h"

static struct Path path_map[50];
static unsigned int distance_map[50][50];
static const char *location_map[50];
char *restrict distances_buffer;
static bool stop_evaluation;
static int total_distance;

static sig_t initial_handler;

void
catch_interrupt(int signal)
{
	const char *restrict failure;

	if (UNLIKELY(!signal_report(&initial_handler,
				    SIGINT,
				    initial_handler,
				    &failure))) {
		free(distances_buffer);
		exit_on_failure(failure);
	}

	stop_evaluation = true;
}

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

		++(*buffer_ptr); /* skip '\t' or final '\n' */
		++distance;
	} while (distance < distance_until);
}


static inline void
init_tsp_state(void)
{
	unsigned int self;
	unsigned int next;
	unsigned int *restrict row;
	unsigned int *restrict next_row;
	struct Path *restrict path;
	const char *restrict buffer;
	const char *restrict failure;
	const char *restrict *restrict location;

	if (UNLIKELY(!read_file(&distances_buffer,
				DISTANCES_PATH,
				&failure)))
	    exit_on_failure(failure);



	buffer	 = distances_buffer;
	location = &location_map[0];
	path	 = &path_map[0];
	row	 = &distance_map[0][0];
	next_row = row + 50;
	self	 = 0u;
	next	 = 1u;

	do {
		get_location(location,
			     &buffer);

		get_distance_row(row,
				 next_row,
				 (const char **) &buffer);

		path->self     = self;
		path->next     = next;
		path->distance = row[next];

		total_distance += path->distance;

		++location;
		++path;
		row = next_row;
		next_row += 50;
		self = next;
		++next;
	} while (next < 50);

	get_location(location,
		     &buffer);

	get_distance_row(row,
			 next_row,
			 (const char **) &buffer);

	path->self     = self;
	path->next     = 0;
	path->distance = row[0];

	total_distance += path->distance;

	if (UNLIKELY(!(   signal_report(&initial_handler,
					SIGINT,
					&catch_interrupt,
					&failure)
		       && random_32_64_constructor(&failure)))) {
		free(distances_buffer);
		exit_on_failure(failure);
	}
}

static inline void
put_path(const struct Path *const restrict path,
	 char *restrict *const restrict buffer_ptr)
{
	char *restrict buffer;

	buffer = *buffer_ptr;

	put_location(&buffer,
		     location_map[path->self]);

	*buffer = '\t'; ++buffer;
	*buffer = 't';	++buffer;
	*buffer = 'o';	++buffer;
	*buffer = '\t'; ++buffer;

	put_location(&buffer,
		     location_map[path->next]);

	*buffer = '\t'; ++buffer;

	put_uint(&buffer,
		 path->distance);

	*buffer = ' ';	++buffer;
	*buffer = 'k';	++buffer;
	*buffer = 'm';	++buffer;
	*buffer = '\n'; ++buffer;

	*buffer_ptr = buffer;
}


static inline void
put_total(char *restrict *const restrict buffer_ptr)
{
	char *restrict buffer;

	buffer = *buffer_ptr;

	*buffer = '\n';	++buffer;
	*buffer = 't';	++buffer;
	*buffer = 'o';	++buffer;
	*buffer = 't';	++buffer;
	*buffer = 'a';	++buffer;
	*buffer = 'l';	++buffer;
	*buffer = ':';	++buffer;
	*buffer = ' ';	++buffer;

	put_uint(&buffer,
		 total_distance);

	*buffer = ' ';	++buffer;
	*buffer = 'k';	++buffer;
	*buffer = 'm';	++buffer;
	*buffer = '\n';	++buffer;

	*buffer_ptr = buffer;
}



static inline void
write_solution(void)
{
	const struct Path *restrict path;
	char *restrict ptr;
	const char *restrict failure;
	static char buffer[SOLUTION_BUFFER_SIZE];


	const struct Path *const restrict first_path = &path_map[0];

	path	  = first_path;
	ptr	  = &buffer[0];

	do {
		put_path(path,
			 &ptr);

		path = &path_map[path->next];
	} while (path != first_path);

	free(distances_buffer);

	put_total(&ptr);

	if (UNLIKELY(!write_file(&buffer[0],
				 ptr - &buffer[0],
				 SOLUTION_PATH,
				 &failure)))
		exit_on_failure(failure);
}

static inline void
sample_paths(struct Path *restrict *const restrict path1_ptr,
	     struct Path *restrict *const restrict path2_ptr)
{
	uint32_t i_path2;
	struct Path *restrict path2;

	const uint32_t i_path1 = random_uint32_upto(49u);

	struct Path *const restrict path1 = &path_map[i_path1];

	while (1) {
		i_path2 = random_uint32_upto(49u);

		if (i_path2 != i_path1) {
			path2 = &path_map[i_path2];

			if (   (path2->next != i_path1)
			    && (path1->next != i_path2)) {

				*path1_ptr = path1;
				*path2_ptr = path2;
				return;
			}
		}
	}
}


static inline int
do_swap_path(struct Path *const restrict path,
	     const unsigned int next)
{
	const unsigned int new_distance = distance_map[path->self][next];

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

static inline bool
make_inferior_transition(const int delta_distance,
			 const double temperature)
{
	const double transition_probability
	= exp(((double) (delta_distance * EXPONENT_CONSTANT)) / temperature);

	/* printf("temperature: %f, transition_probability: %f\n", */
	/*        temperature, */
	/*        transition_probability); */

	return transition_probability > random_probability();
}

static inline void
evaluate(void)
{
	struct Path *restrict path1;
	struct Path *restrict path2;
	unsigned int old_next2;
	unsigned int old_distance1;
	unsigned int old_distance2;
	double temperature;
	int delta_distance;
	const char *restrict failure;


	/* static const struct timespec sleep_time = { */
	/* 	.tv_nsec = 10000000 */
	/* }; */
	/* struct timespec buffer_time; */

	temperature = INITIAL_TEMPERATURE;

	do {
		sample_paths(&path1,
			     &path2);

		old_distance1 = path1->distance;
		old_distance2 = path2->distance;

		delta_distance = swap_paths(path1,
					    path2);

		/* printf("delta_distance: %d\n", */
		/*        delta_distance); */

		if (   (delta_distance < 0)
		    || make_inferior_transition(delta_distance,
						temperature)) {
			total_distance += delta_distance;

		} else {
			old_next2   = path1->next;
			path1->next = path2->next;
			path2->next = old_next2;

			path1->distance = old_distance1;
			path2->distance = old_distance2;
		}

		/* (void) nanosleep(&sleep_time, */
		/* 		 &buffer_time); */

		temperature -= DELTA_TEMPERATURE;

	} while (!stop_evaluation && (temperature >= 0.0));


	if (UNLIKELY(!file_write_report(STDOUT_FILENO,
					"\ndone!\n",
					sizeof("\ndone!\n") - 1,
					&failure))) {
		free(distances_buffer);
		exit_on_failure(failure);
	}
}

int
main(void)
{
	init_tsp_state();

	evaluate();

	write_solution();

	return 0;
}

