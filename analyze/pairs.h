#ifndef ANALYZE_PAIRS_H_
#define ANALYZE_PAIRS_H_

void run_pairs(void);

struct DblNode {
	double value;
	struct DblNode *prev;
	struct DblNode *next;
};

static inline int compare_dbl_nodes(struct DblNode *node1,
				    struct DblNode *node2);

static inline void swap_dbl_nodes(struct DblNode *node1,
				  struct DblNode *node2);

void init_nuts_and_bolts(struct DblNode *nuts,
			 struct DblNode *bolts,
			 const size_t count);

static inline void print_nuts_and_bolts(struct DblNode *nuts,
					struct DblNode *bolts);

static inline void match_nuts_and_bolts(struct DblNode *nuts,
					struct DblNode *bolts,
					const size_t count);
#endif /* ifndef ANALYZE_PAIRS_H_ */
