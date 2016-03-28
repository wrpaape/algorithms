#include "graphs.h"
#include "builder.h"
#include "bheap.h"
#include "inspect.h"

int max_cost(const void *edge1, const void *edge2)
{
	return (((struct Edge *) edge1)->cost) >
	       (((struct Edge *) edge2)->cost);
}

int main(void)
{


	/* tour_graph(build_graph1()); */

	int costs[] = {12, 1, 3, 55, 98, -10, 2293, -500, 123, 10};
	/* int costs[] = {12, 1}; */

	struct Edge **edges;

	HANDLE_MALLOC(edges, sizeof(struct Edge *) * 10lu);


	for (size_t i = 0lu; i < 10lu; ++i) {
		HANDLE_MALLOC(edges[i], sizeof(struct Edge));
		edges[i]->next = NULL;
		edges[i]->cost = costs[i];
	}


	struct BHeap *heap = array_into_bheap(10lu, (void **) edges, max_cost);

	print_edge_bheap(heap);

	printf("\n\nextracted cost: %d\n\n",
	       ((struct Edge *) bheap_extract(heap))->cost);

	print_edge_bheap(heap);

	printf("\n\nextracted cost: %d\n\n",
	       ((struct Edge *) bheap_extract(heap))->cost);

	print_edge_bheap(heap);

	printf("\n\nextracted cost: %d\n\n",
	       ((struct Edge *) bheap_extract(heap))->cost);

	print_edge_bheap(heap);

	printf("\n\nextracted cost: %d\n\n",
	       ((struct Edge *) bheap_extract(heap))->cost);

	print_edge_bheap(heap);

	return 0;
}
