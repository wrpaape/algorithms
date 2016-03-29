#include <time.h>
#define MAX_RAND (1u << 32)

extern inline void init_rng(void);
extern inline int rand_in_range(const int lbound,
				const int rbound);
{


	printf("rng: %u\n", (unsigned) pcg32_random_r(rngptr));

	return 0;
}
