#include "suffix_tree.h"

int main(void)
{
	const char *string = "rooty tooty point and shooty";

	struct SuffixTree *tree = build_suffix_tree(string);

	free_suffix_tree(tree);

	puts("DONE");

	return 0;
}
