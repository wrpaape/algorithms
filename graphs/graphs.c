#include "graphs.h"
#include "builder.h"
#include "inspect.h"
#include "bheap.h"

int max_cost(const void *edge1, const void *edge2)
{
	return (((struct Edge *) edge1)->cost) >
	       (((struct Edge *) edge2)->cost);
}

int main(void)
{


	/* tour_graph(build_graph1()); */

	int costs[] = {12, 1, 3, 55, 98, -10, 2293};

	struct Edge *edges[7lu];

	for (int i = 0; i < 7; ++i) {
		HANDLE_MALLOC(edges[i], sizeof(struct Edge));
		edges[i]->cost = costs[i];
	}


	struct BHeap *heap = array_into_bheap(7lu,
					      (void **) edges,
					      max_cost);

	void **nodes = heap->nodes;

	for (size_t i = 1; i < 8lu; ++i) {
		printf("nodes[%zu]: %d\n", i, ((struct Edge *) nodes[i])->cost);
		fflush(stdout);
	}



	return 0;
}
