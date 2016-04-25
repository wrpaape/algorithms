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

static inline void remove_dbl_node(struct DblNode *node);

static inline void splice_dbl_node(struct DblNode *node,
				   struct DblNode *prev,
				   struct DblNode *next);

void do_match(struct DblNode **matched_nuts,
	      struct DblNode **matched_blts,
	      struct DblNode *head_nut,
	      struct DblNode *last_nut,
	      struct DblNode *head_blt,
	      struct DblNode *last_blt);

void init_nuts_and_bolts(struct DblNode *nuts,
			 struct DblNode *bolts,
			 const size_t count);

void print_nuts_and_bolts(struct DblNode *nuts,
			  struct DblNode *blts);

static inline void match_nuts_and_bolts(struct DblNode *restrict nuts,
					struct DblNode *restrict blts,
					const size_t count);
#endif /* ifndef ANALYZE_PAIRS_H_ */
