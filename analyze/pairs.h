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

static inline struct DblNode **enqueue_dbl_node(struct DblNode **qend,
						struct DblNode *node)

void do_match(struct DblNode *nut_head,
	      struct DblNode *nut_last,
	      struct DblNode *blt_head,
	      struct DblNode *blt_last);

void init_nuts_and_bolts(struct DblNode *nuts,
			 struct DblNode *bolts,
			 const size_t count);

void print_nuts_and_bolts(struct DblNode *nuts,
			  struct DblNode *blts);

static inline void match_nuts_and_bolts(struct DblNode **restrict nut_head,
					struct DblNode **restrict blt_head,
					struct DblNode *restrict nuts,
					struct DblNode *restrict bolts,
					const size_t count);
#endif /* ifndef ANALYZE_PAIRS_H_ */
