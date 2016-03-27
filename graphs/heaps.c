#include "graphs.h"
#include "heaps.h"
#include <limits.h>


struct BinaryHeap *init_binary_heap(const size_t node_size,
				    int (*compare)(const void *,
						   const void *))
{
	struct BinaryHeap *heap;

	HANDLE_MALLOC(heap, sizeof(struct BinaryHeap));
	HANDLE_MALLOC(heap->nodes, node_size * 1lu);

	heap->count   = 0lu;
	heap->alloc   = 1lu;
	heap->compare = compare;

	return heap;
}



struct BinaryHeap *array_into_binary_heap(const size_t length,
					  const void **array,
					  int (*compare)(const void *,
							 const void *))
{
	struct BinaryHeap *heap = init_binary_heap(compare);

	binary_heap_insert_array(heap, length, array);

	return heap;
}

void binary_heap_insert_array(struct BinaryHeap *heap,
			      const size_t length,
			      const void **array)
{
	for (size_t i = 0; i < length; ++i)
		binary_heap_insert_value(heap, array[i]);
}


void binary_heap_insert_value(struct BinaryHeap *heap, const void *next)
{
	insert(heap->nodes, heap->count, value, heap->compare);

	if (heap->count == heap->alloc)
		resize_binary_heap(heap, heap->alloc * 2);

}

static void insert(void **nodes,
		   const size_t base_i,
		   const void *next,
		   int (*compare)(const void *,
				  const void *))
{
	const size_t par_i  = base_i / 2;
	const void *parent = nodes[par_i];

	if (compare(parent, next)) {
		nodes[base_i] = next;
		return;
	}

	nodes[base_i] = parent;
	insert(nodes, par_i, parent, compare);
}

inline void resize_binary_heap(struct BinaryHeap *heap, const size_t size)
{
	if (realloc(heap->nodes, sizeof(int) * size) == NULL) {
		EXIT_ON_FAILURE("failed to reallocate number of words"
				"from %lu to %lu",
				heap->alloc, size);
	}

	heap->alloc = size;
}
