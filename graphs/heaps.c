#include "graphs.h"
#include "heaps.h"
#include <limits.h>


struct BinaryHeap *init_binary_heap(int (*compare)(const node_t,
						   const node_t))
{
	struct BinaryHeap *heap;

	HANDLE_MALLOC(heap, sizeof(struct BinaryHeap));
	HANDLE_MALLOC(heap->nodes, sizeof(int) * 2);

	/* set first node as sentinel, will never move */
	heap->nodes[0]	  = compare(INT_MIN, INT_MAX) ? INT_MIN : INT_MAX;
	heap->count = 1lu;
	heap->alloc = 2lu;

	return heap;
}



struct BinaryHeap *array_into_binary_heap(int length,
					  node_t *array,
					  int (*compare)(const node_t,
							 const node_t))
{
	struct BinaryHeap *heap = init_binary_heap(compare);

	binary_heap_insert_array(heap, length, array);

	return heap;
}

void binary_heap_insert_array(struct BinaryHeap *heap,
			      const size_t length,
			      node_t *array)
{
	for (int i = 0; i < length; ++i)
		binary_heap_insert_value(heap, array[i]);
}


void binary_heap_insert_value(struct BinaryHeap *heap, const node_t value)
{
	insert(heap->nodes, heap->count, value, heap->compare);

	if (heap->count == heap->alloc)
		resize_binary_heap(heap, heap->alloc * 2);

}

void insert(int *nodes, int base_i, int value, int (*compare)(int, int))
{
	int par_i  = base_i / 2;
	int parent = nodes[par_i];

	if (compare(parent, value)) {

		nodes[base_i] = value;
		return;
	}

	nodes[base_i] = parent;
	insert(nodes, par_i, value, compare);
}

inline void resize_binary_heap(struct BinaryHeap *heap, size_t size)
{
	if (realloc(heap->nodes, sizeof(int) * size) == NULL) {
		EXIT_ON_FAILURE("failed to reallocate number of words"
				"from %lu to %lu",
				heap->alloc, size);
	}

	heap->alloc = size;
}
