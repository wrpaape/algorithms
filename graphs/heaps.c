#include "graphs.h"
#include "heaps.h"


struct BinaryHeap *init_binary_heap(const size_t node_size,
				    int (*compare)(const void *,
						   const void *))
{
	struct BinaryHeap *heap;

	HANDLE_MALLOC(heap, sizeof(struct BinaryHeap));
	HANDLE_MALLOC(heap->nodes, sizeof(void *) * 2lu);
	HANDLE_MALLOC(heap->nodes[1], node_size);

	heap->count   = 1lu;
	heap->alloc   = 2lu;
	heap->compare = compare;

	return heap;
}



struct BinaryHeap *array_into_binary_heap(const size_t length,
					  const size_t node_size,
					  void **array,
					  int (*compare)(const void *,
							 const void *))
{
	struct BinaryHeap *heap = init_binary_heap(node_size, compare);

	binary_heap_insert_array(heap, length, array);

	return heap;
}

void binary_heap_insert_array(struct BinaryHeap *heap,
			      const size_t length,
			      void **array)
{
	for (size_t i = 0; i < length; ++i)
		binary_heap_insert_value(heap, array[i]);
}


void binary_heap_insert_value(struct BinaryHeap *heap, void *next)
{
	insert(heap->nodes, next, heap->count, heap->compare);

	++(heap->count);

	if (heap->count == heap->alloc)
		resize_binary_heap(heap, heap->alloc * 2lu);

}

void insert(void **nodes,
	    void *next,
	    const size_t base_i,
	    int (*compare)(const void *,
			   const void *))
{
	/* sentinel node has been reached, 'next' is new root */
	if (base_i == 1lu) {
		nodes[1lu] = next;
		return;
	}
	const size_t par_i = base_i / 2lu;
	void *parent = nodes[par_i];

	if (compare(parent, next)) {
		nodes[base_i] = next;
		return;
	}

	nodes[base_i] = parent;
	insert(nodes, parent, par_i, compare);
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
