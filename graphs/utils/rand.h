#ifndef GRAPHS_UTILS_RAND_H_
#define GRAPHS_UTILS_RAND_H_ value
#include <pcg_basic.h> /* psuedorandom number generator */
#include <time.h>      /* unique seed */

pcg32_random_t _RNG;

inline void init_rng(void)
{
	pcg32_srandom_r(&_RNG, time(NULL), (intptr_t)&_RNG);
}
/* static inline int rand_in_range(pcg32_random_t *_RNG, */
inline int rand_in_range(const int lbound,
			 const int rbound);
{

	printf("rand: %u\n", (unsigned) pcg32_random_r(&_RNG));

	return 0;
}
#endif /* ifndef GRAPHS_UTILS_RAND_H_ */
