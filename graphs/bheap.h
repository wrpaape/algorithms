struct BHeap {
	/* size_t node_size; */
	size_t count;
	size_t alloc;
	void **nodes;
	int (*compare)(const void *,
		       const void *);
};

/* initialize, destroy, resize
 ******************************************************************************/
inline struct BHeap *init_bheap(int (*compare)(const void *,
					       const void *))
{
	struct BHeap *heap;

	HANDLE_MALLOC(heap, sizeof(struct BHeap));
	HANDLE_MALLOC(heap->nodes, sizeof(void *) * 2lu);

	/* include sentinel node at index 0 in 'count', i.e. count >= 1 */
	heap->count   = 1lu;
	heap->alloc   = 2lu;
	heap->compare = compare;

	return heap;
}

inline void free_bheap(struct BHeap *heap)
{
	free(heap->nodes);
	free(heap);
}

static inline void resize_bheap(struct BHeap *heap,
				const size_t size);


/* insertion
 ******************************************************************************/
void bheap_insert(struct BHeap *heap,
		  void *next);

void bheap_insert_array(struct BHeap *heap,
			const size_t length,
			void **array);

void do_insert(void **nodes,
	       void *next,
	       const size_t next_i,
	       int (*compare)(const void *,
			      const void *));




/* extraction
 ******************************************************************************/
void *bheap_extract(struct BHeap *heap);

void do_shift(void **nodes,
	      void *next,
	      const size_t next_i,
	      const size_t penult_i,
	      int (*compare)(const void *,
			     const void *));



/* display
 ******************************************************************************/




/* convenience, misc
 ******************************************************************************/
struct BHeap *array_into_bheap(const size_t length,
			       void **array,
			       int (*compare)(const void *,
					      const void *));
