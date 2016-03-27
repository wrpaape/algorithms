#include "graphs.h"
#include "builder.h"
#include "inspect.h"
#include "heaps.h"

int max_integer(const void *num1, const void *num2)
{
	return ((size_t) num1) > ((size_t) num2);
}

int main(void)
{

	/* tour_graph(build_graph1()); */

	size_t array[] = {4, 5, 1, 2, 3};

	struct BinaryHeap *heap = array_into_binary_heap(5lu,
							 (void **) array,
							 max_integer);

	puts("hi");

	void **nodes = heap->nodes;

	for (size_t i = 1; i < 6; ++i) {
		printf("nodes[%zu]: %zu\n", i, (size_t) nodes[i]);
		fflush(stdout);
	}



	return 0;
}
