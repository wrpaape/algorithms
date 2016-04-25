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

void do_match(struct DblNode *prev_nut,
	      struct DblNode *next_nut,
	      struct DblNode *prev_blt,
	      struct DblNode *next_blt);

void init_nuts_and_bolts(struct DblNode *nuts,
			 struct DblNode *bolts,
			 const size_t count);

void print_dbl_nodes(struct DblNode *head_node,
		     struct DblNode *last_node);

void print_nuts_and_bolts(struct DblNode *restrict nuts,
			  struct DblNode *restrict blts);

static inline void match_nuts_and_bolts(struct DblNode **restrict matched_nuts,
					struct DblNode **restrict matched_blts,
					struct DblNode *prev_nut,
					struct DblNode *prev_blt,
					const size_t count);
#endif /* ifndef ANALYZE_PAIRS_H_ */
