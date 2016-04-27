#include <utils/utils.h>
#include <utils/rand.h>

struct BitVector {
	int *bits;
	size_t size;
	size_t alloc;
};

struct IntHeap {
	int *nodes;
	size_t count;
};

void run_grinch(void);
void run_set_union(void);
void run_heap(void);


static inline struct IntHeap *init_heap(const size_t alloc);

static inline void heap_insert(struct IntHeap *heap,
			       const int next);

void do_insert_next(int *const nodes,
		    const int next,
		    const ptrdiff_t i_next);

struct BitVector *init_rand_bit_vector(const size_t size,
				       const int min,
				       const int max);

static inline void do_sort(int *data,
			   const ptrdiff_t from,
			   const ptrdiff_t upto);

ptrdiff_t split_data(int *data,
		     ptrdiff_t from,
		     ptrdiff_t upto);
