#include <graphs.h>
#include <heaps.h>

struct BinaryHeap *init_binary_heap(int root_value, int (*compare)(int, int))
{
	struct BinaryHeap *heap;
	struct HeapNode *root;

	HANDLE_MALLOC(heap, sizeof(struct BinaryHeap));
	HANDLE_MALLOC(root, sizeof(struct HeapNode));

	root->value  = root_value;
	root->parent = NULL;
	root->lchild = NULL;
	root->rchild = NULL;

	heap->compare = compare;
	heap->root    = root;
}

void binary_heap_insert_array(struct BinaryHeap *heap, int length, int *array)
{




	for (int i = 0; i < length; ++i) {
		binary_heap_insert()
	}

	return heap;
}


void binary_heap_insert_value(struct BinaryHeap *heap, int value)
