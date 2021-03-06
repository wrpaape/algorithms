#include <utils/utils.h>
#include <utils/rand.h>

#define BYTE_MAX UCHAR_MAX
#define HASH_MAX ULLONG_MAX

typedef unsigned long long int hash_t;
typedef unsigned char byte_t;

struct BitVector {
	int min;
	int max;
	size_t span_m1;
	size_t lg_span;
	size_t size;
	uint64_t *bits;
};

struct IntHeap {
	int *nodes;
	size_t count;
};

void run_grinch(void);
void run_set_union(void);
void run_heap(void);
void run_hash_test(void);


hash_t hash_bytes(byte_t *bytes,
		  const size_t length,
		  const hash_t m_prime);

static inline struct IntHeap *init_heap(const size_t alloc);

static inline void heap_insert(struct IntHeap *heap,
			       const int next);

static inline int heap_extract(struct IntHeap *heap);

void do_insert_next(int *const nodes,
		    const int next,
		    const ptrdiff_t i_next);

void do_shift_next(int *const nodes,
		    const int next,
		    const ptrdiff_t i_next,
		    const ptrdiff_t i_base);

bool bit_vector_put(struct BitVector *set,
		    const int x);

static inline void print_bit_vector(struct BitVector *set);

static inline void free_bit_vector(struct BitVector *set);

struct BitVector *init_rand_bit_vector(const size_t size,
				       const int min,
				       const int max);

static inline void do_sort(int *data,
			   const ptrdiff_t from,
			   const ptrdiff_t upto);

ptrdiff_t split_data(int *data,
		     ptrdiff_t from,
		     ptrdiff_t upto);
