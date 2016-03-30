#include "graphs.h"
#include "utils/utils.h"
#include "builder.h"
#include "bheap.h"
#include "inspect.h"
#include "maps/maker.h"
#include "maps/printer.h"

#define FILENAME "maps/map.csv"

int min_cost(const void *vedge1, const void *vedge2)
{
	return (((struct Edge *) vedge1)->cost) <
	       (((struct Edge *) vedge2)->cost);
}


int main(void)
{
	char buffer[1lu << 17];
	struct CostMap *map = make_cost_map(80lu, 40lu, 1, 9);

	cost_map_to_csv(FILENAME, map);

	pretty_print_cost_map(buffer, map);

	puts(buffer);

	free_cost_map(map);

	return 0;

	/* tour_graph(build_graph1()); */

	/* int costs[] = {12, 1, 3, 55, 98, -10, 2293, -500, 123, 10}; */
	/* int costs[] = {12, 1}; */

	/* struct Edge **edges; */

	/* HANDLE_MALLOC(edges, sizeof(struct Edge *) * 10lu); */

	/* for (size_t i = 0lu; i < 10lu; ++i) { */
	/* 	HANDLE_MALLOC(edges[i], sizeof(struct Edge)); */
	/* 	edges[i]->next = NULL; */
	/* 	edges[i]->cost = costs[i]; */
	/* } */

	/* struct BHeap *heap = array_into_bheap(10lu, (void **) edges, min_cost); */

	/* print_bheap(heap, edge_to_string); */

	/* printf("\n\nextracted cost: %d\n\n\n", */
	/*        ((struct Edge *) bheap_extract(heap))->cost); */

	/* print_bheap(heap, edge_to_string); */

	/* printf("\n\nextracted cost: %d\n\n\n", */
	/*        ((struct Edge *) bheap_extract(heap))->cost); */

	/* print_bheap(heap, edge_to_string); */

	/* printf("\n\nextracted cost: %d\n\n\n", */
	/*        ((struct Edge *) bheap_extract(heap))->cost); */

	/* print_bheap(heap, edge_to_string); */

	/* printf("\n\nextracted cost: %d\n\n\n", */
	/*        ((struct Edge *) bheap_extract(heap))->cost); */

	/* print_bheap(heap, edge_to_string); */

	/* return 0; */
}
