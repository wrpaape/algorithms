#include "graphs.h"
#include "bheap.h"


/* initialize, destroy, resize
 ******************************************************************************/
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
	const size_t count = heap->count;
	const size_t next_count = count + length;

	if (heap->alloc < next_count)
		resize_bheap(heap, next_pow_two(next_count));

	void **nodes = heap->nodes;
	int (*compare)(const void *,
		       const void *) = heap->compare;


	for (size_t i = 0lu; i < length; ++i)
		do_insert(nodes, array[i], count + i, compare);

	heap->count = next_count;
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
		nodes[1lu] = next;
		return;
	}


	const size_t parent_i = next_i / 2lu;
	void *parent	      = nodes[parent_i];

	if (compare(parent, next)) {
		nodes[next_i] = next;
		return;
	}

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
	void *base   = nodes[heap->count];

	do_shift(nodes, base, 1lu, heap->count / 2lu, heap->compare);

	return root;
}

void do_shift(void **nodes,
	      void *next,
	      const size_t next_i,
	      const size_t base_par_i,
	      int (*compare)(const void *,
			     const void *))
{
	/* base level of heap has been reached (no more children), replace */
	if (next_i > base_par_i) {
		nodes[next_i] = next;
		return;
	}

	const size_t lchild_i = next_i * 2lu;
	const size_t rchild_i = lchild_i + 1lu;

	void *lchild = nodes[lchild_i];
	void *rchild = nodes[rchild_i];

	/* compare with left child */
	if (compare(lchild, next)) {

		if (compare(lchild, rchild)) {
			nodes[next_i] = lchild;
			do_shift(nodes, next, lchild_i, base_par_i, compare);
		} else {
			nodes[next_i] = rchild;
			do_shift(nodes, next, rchild_i, base_par_i, compare);
		}

		return;
	}



	/* compare with right child */
	if (compare(rchild, next)) {
		nodes[next_i] = rchild;
		do_shift(nodes, next, rchild_i, base_par_i, compare);
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

inline size_t next_pow_two(size_t num)
{
	return 1lu << ((sizeof(size_t) * CHAR_BIT) - __builtin_clzl(num));
}

