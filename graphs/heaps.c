#include "graphs.h"
#include "heaps.h"
#include "limits.h"


struct BinaryHeap *init_binary_heap(int (*compare)(int, int))
{
	struct BinaryHeap *heap;

	HANDLE_MALLOC(heap, sizeof(struct BinaryHeap));
	HANDLE_MALLOC(heap->nodes, sizeof(int) * 2);

	/* set first node as sentinel, will never move */
	heap->nodes[0]	  = compare(INT_MIN, INT_MAX) ? INT_MIN : INT_MAX;
	heap->nodes_count = 1lu;
	heap->alloc_count = 2lu;

	return heap;
}



struct BinaryHeap *array_into_binary_heap(int length,
					  int *array,
					  int (*compare)(int, int))
{
	struct BinaryHeap *heap = init_binary_heap(compare);

	binary_heap_insert_array(heap, length, array);

	return heap;
}

void binary_heap_insert_array(struct BinaryHeap *heap, int length, int *array)
{
	for (int i = 0; i < length; ++i)
		binary_heap_insert_value(heap, array[i]);
}


void binary_heap_insert_value(struct BinaryHeap *heap, int value)
{
	insert(heap->nodes, heap->nodes_count, value, heap->compare);

	if (heap->nodes_count == heap->alloc_count)
		resize_binary_heap(heap, heap->alloc_count * 2);

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
				heap->alloc_count, size);
	}

	heap->alloc_count = size;
}
