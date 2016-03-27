struct HeapNode {
	int value;
	struct HeapNode *parent;
	struct HeapNode *lchild;
	struct HeapNode *rchild;
};

struct BinaryHeap {
	int (*compare)(int, int);
	struct HeapNode *root;
	struct HeapNode *base;
};

struct BinaryHeap *init_binary_heap(int root_value, int (*compare)(int, int));
void binary_heap_insert_array(struct BinaryHeap *heap, int length, int *array);
void binary_heap_insert_value(struct BinaryHeap *heap, int value);
