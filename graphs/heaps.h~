struct BinaryHeap {
	int (*compare)(const void *,
		       const void *);
	void **nodes;
	size_t count;
	size_t alloc;
};

struct BinaryHeap *init_binary_heap(const size_t node_size,
				    int (*compare)(const void *,
						   const void *));

struct BinaryHeap *array_into_binary_heap(const size_t length,
					  const void **array,
					  int (*compare)(const void *,
							 const void *));

void binary_heap_insert_array(struct BinaryHeap *heap,
			      const size_t length,
			      const void **array);

void binary_heap_insert_value(struct BinaryHeap *heap, const void *next);

static void insert(void **nodes,
		   const size_t base_i,
		   const void *next,
		   int (*compare)(const void *,
				  const void *));

static inline void resize_binary_heap(struct BinaryHeap *heap, const size_t size);
