#ifndef ANALYZE_PAIRS_H_
#define ANALYZE_PAIRS_H_

void run_pairs(void);

int compare(double x, double y);

static inline void init_nuts_and_bolts(double *nuts,
				       double *bolts,
				       const size_t count);

static inline void print_nuts_and_bolts(double *nuts,
					double *bolts,
					const size_t count);
#endif /* ifndef ANALYZE_PAIRS_H_ */
