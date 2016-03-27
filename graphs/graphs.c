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

	const int array[] = {4, 5, 1, 2, 3};

	array_into_binary_heap(5lu, sizeof(int), (void **) array, max_integer);



	return 0;
}
