struct BinaryHeap {
	size_t count;
	size_t alloc;
	void **nodes;
	int (*compare)(const void *,
		       const void *);
};

struct BinaryHeap *init_binary_heap(const size_t node_size,
				    int (*compare)(const void *,
						   const void *));

struct BinaryHeap *array_into_binary_heap(const size_t length,
					  const size_t node_size,
					  void **array,
					  int (*compare)(const void *,
							 const void *));

void binary_heap_insert_array(struct BinaryHeap *heap,
			      const size_t length,
			      void **array);

void binary_heap_insert_value(struct BinaryHeap *heap, void *next);

void insert(void **nodes,
	    void *next,
	    const size_t base_i,
	    int (*compare)(const void *,
			   const void *));

static inline void resize_binary_heap(struct BinaryHeap *heap, const size_t size);
