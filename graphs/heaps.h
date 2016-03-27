struct BinaryHeap {
	int (*compare)(const node_t,
		       const node_t);
	node_t **nodes;
	size_t count;
	size_t alloc;
};

struct BinaryHeap *init_binary_heap(int (*compare)(const node_t,
						   const node_t));

struct BinaryHeap *array_into_binary_heap(int length,
					  node_t *array,
					  int (*compare)(const node_t,
							 const node_t));

void binary_heap_insert_array(struct BinaryHeap *heap,
			      const size_t length,
			      node_t *array);

void binary_heap_insert_value(struct BinaryHeap *heap, const node_t value);

static void insert(node_t **nodes,
		   node_t base_i,
		   node_t value,
		   int (*compare)(const node_t,
				  const node_t));

static inline void resize_binary_heap(struct BinaryHeap *heap, size_t size);
