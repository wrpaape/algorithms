#include <utils/utils.h>
#include <utils/rand.h>
#include <bheap/bheap.h>

struct BitVector {
	int *bits;
	size_t size;
	size_t alloc;
};

void run_grinch(void);
void run_set_union(void);

struct BitVector *init_rand_bit_vector(const size_t size,
				       const int min,
				       const int max);

static inline void do_sort(int *data,
			   const ptrdiff_t from,
			   const ptrdiff_t upto);

static inline void swap_ij(int *data,
			   const ptrdiff_t i,
			   const ptrdiff_t j);

ptrdiff_t split_data(int *data,
		     ptrdiff_t from,
		     ptrdiff_t upto);

int compare(const void *x,
	    const void *y);

 void node_to_string(char *buffer,
		     const void *node);
