#include "utils/utils.h"
#include "utils/rand.h"
#include "tree_compare.h"
#include "pairs.h"
#include "analyze.h"

#define TOTAL_COUNT_PROCEDURES 2lu
#define DEF_PROC_I 1lu

static void (*PROC_MAP[])(void) = {
	&run_tree_compare,
	&run_pairs
};

int main(int argc, char *argv[])
{
	if (argc == 1) {
		void (*procedures[1ul])(void) = {
			PROC_MAP[DEF_PROC_I]
		};

		run_procedures(&procedures[0ul], 1ul);

		return 0;
	}


	const size_t count = argc - 1ul;

	void (*procedures[count])(void);

	parse_procedures(&procedures[0ul], &argv[1ul], count);

	run_procedures(&procedures[0ul], count);

	return 0;
}

void parse_procedures(void (**procedures)(void),
		      char *args[],
		      const size_t count)
{
	if (count > TOTAL_COUNT_PROCEDURES)
		EXIT_ON_FAILURE("too many procedures!");

	long proc_i;

	for (size_t i = 0ul; i < count; ++i) {
		proc_i = strtol(args[i], NULL, 10) - 1l;

		if ((proc_i < 0ul) || (proc_i >= TOTAL_COUNT_PROCEDURES))
			EXIT_ON_FAILURE("invalid procedure: %ld", proc_i);

		procedures[i] = PROC_MAP[proc_i];
	}
}

void run_procedures(void (**procedures)(void),
		       const size_t count)
{
	clock_t time_start;
	clock_t time_finish;

	init_rng();

	for (size_t i = 0ul, j = 1ul; i < count; i = j, ++j) {

		printf("\nRUNNING PROCEDURE %zu of %zu...\n\n", j, count);

		time_start  = clock();
		procedures[i]();
		time_finish = clock();

		printf("\nFINISHED IN %zu µs\n", time_finish - time_start);
	}

}
