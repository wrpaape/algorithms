#include "graphs.h"
#include "builder.h"
#include "inspect.h"
#include "heaps.h"

int max_integer(const void *num1, const void *num2)
{
	return ((int) num1) > ((int) num2);
}

int main(void)
{

	/* tour_graph(build_graph1()); */

	int array[] = {4, 5, 1, 2, 3};

	struct BinaryHeap *heap = array_into_binary_heap(5lu,
							 (void **) array,
							 max_integer);

	puts("hi");

	int **nodes = (int **) heap->nodes;

	for (int i = 1; i < 6; ++i) {
		printf("nodes[%d]: %d\n", i, *nodes[i]);
		fflush(stdout);
	}



	return 0;
}
