struct BinaryHeap {
	int (*compare)(int, int);
	int *nodes;
	size_t nodes_count;
	size_t alloc_count;
};

struct BinaryHeap *init_binary_heap(int (*compare)(int, int));

struct BinaryHeap *array_into_binary_heap(int length,
					  int *array,
					  int (*compare)(int, int));

void binary_heap_insert_array(struct BinaryHeap *heap, int length, int *array);

void binary_heap_insert_value(struct BinaryHeap *heap, int value);

static void insert(int *nodes, int par_i, int value, int (*compare)(int, int));

static inline void resize_binary_heap(struct BinaryHeap *heap, size_t size);


