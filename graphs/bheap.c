#include "graphs.h"
#include "bheap.h"


/* initialize, destroy, resize
 ******************************************************************************/
extern inline struct BHeap *init_bheap(int (*compare)(const void *,
						      const void *));

extern inline void free_bheap(struct BHeap *heap);

inline void resize_bheap(struct BHeap *heap, const size_t size)
{
	if (realloc(heap->nodes, sizeof(void *) * size) == NULL) {
		EXIT_ON_FAILURE("failed to reallocate number of words"
				"from %lu to %lu",
				heap->alloc, size);
	}

	heap->alloc = size;
}









/* insertion
 ******************************************************************************/
void bheap_insert_array(struct BHeap *heap,
			const size_t length,
			void **array)
{
	for (size_t i = 0lu; i < length; ++i)
		bheap_insert(heap, array[i]);
}


void bheap_insert(struct BHeap *heap,
		  void *next)
{
	insert_next(heap->nodes, next, heap->count, heap->compare);

	++(heap->count);

	if (heap->count == heap->alloc)
		resize_bheap(heap, heap->alloc * 2lu);
}


void insert_next(void **nodes,
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
	insert_next(nodes, next, par_i, compare);
}




/* extraction
 ******************************************************************************/
void *bheap_extract(struct BHeap *heap)
{
	--(heap->count);

	void **nodes = heap->nodes;
	void *root   = nodes[1lu];
	void *next   = nodes[heap->count];


	return root;
}




/* convenience, misc
 ******************************************************************************/
struct BHeap *array_into_bheap(const size_t length,
			       void **array,
			       int (*compare)(const void *,
					      const void *))
{
	struct BHeap *heap = init_bheap(compare);

	bheap_insert_array(heap, length, array);

	return heap;
}
