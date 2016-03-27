#include "graphs.h"
#include "bheap.h"


/* initialize, destroy, resize
 ******************************************************************************/
/* extern inline struct BHeap *init_bheap(size_t node_size, */
extern inline struct BHeap *init_bheap(int (*compare)(const void *,
						      const void *));

extern inline void free_bheap(struct BHeap *heap);

inline void resize_bheap(struct BHeap *heap, const size_t size)
{
	void **nodes = realloc(heap->nodes, sizeof(void *) * size);

	if (nodes == NULL) {
		EXIT_ON_FAILURE("failed to reallocate number of nodes"
				"from %lu to %lu",
				heap->alloc, size);
	}


	heap->nodes = nodes;
	heap->alloc = size;
}









/* insertion
 ******************************************************************************/
void bheap_insert_array(struct BHeap *heap,
			const size_t length,
			void **array)
{
	for (size_t i = 0lu; i < length; ++i) {
		printf("inserting el %zu\n", i);
		bheap_insert(heap, array[i]);
	}
}


void bheap_insert(struct BHeap *heap,
		  void *next)
{
	do_insert(heap->nodes, next, heap->count, heap->compare);

	++(heap->count);


	if (heap->count == heap->alloc)
		resize_bheap(heap, heap->alloc * 2lu);
}


void do_insert(void **nodes,
	       void *next,
	       const size_t next_i,
	       int (*compare)(const void *,
			      const void *))
{
	/* sentinel node has been reached, 'next' is new root node */
	if (next_i == 1lu) {
		puts("     inserting at 1");
		nodes[1lu] = next;
		return;
	}


	const size_t parent_i = next_i / 2lu;
	void *parent	      = nodes[parent_i];

	if (compare(parent, next)) {

		printf("     inserting at:   %zu\n", next_i);
		nodes[next_i] = next;
		return;
	}
		printf("parent_i: %zu\n", parent_i);

	nodes[next_i] = parent;
	do_insert(nodes, next, parent_i, compare);
}




/* extraction
 ******************************************************************************/
void *bheap_extract(struct BHeap *heap)
{
	--(heap->count);

	void **nodes = heap->nodes;
	void *root   = nodes[1lu];

	do_shift(nodes, root, 1lu, heap->count, heap->compare);

	return root;
}

void do_shift(void **nodes,
	      void *next,
	      const size_t next_i,
	      const size_t penult_i,
	      int (*compare)(const void *,
			     const void *))
{
	/* base level of heap has been reached (no more children), replace */
	if (next_i >= penult_i) {
		nodes[next_i] = next;
		return;
	}

	size_t child_i = next_i * 2lu;
	void *child    = nodes[child_i];

	/* compare with left child */
	if (compare(child, next)) {
		nodes[next_i] = child;
		do_shift(nodes, next, child_i, penult_i, compare);
		return;
	}

	++child_i;
	child = nodes[child_i];

	/* compare with right child */
	if (compare(child, next)) {
		nodes[next_i] = child;
		do_shift(nodes, next, child_i, penult_i, compare);
		return;
	}

	/* otherwise, 'next' belongs at index 'next_i' */
	nodes[next_i] = next;
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
