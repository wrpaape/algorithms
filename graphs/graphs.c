#include "graphs.h"
#include "builder.h"

const char *LABELS[] = {
	[START] = "start",  [GOAL ] = "goal!",  [NODE1] = "node 1",
	[NODE2] = "node 2", [NODE3] = "node 3", [NODE4] = "node 4",
	[NODE5] = "node 5", [NODE6] = "node 6", [NODE7] = "node 7",
	[TEL1A] = "teleporter entrance 1", [TEL2A] = "teleporter entrance 2",
	[TEL3A] = "teleporter entrance 3", [TEL4A] = "teleporter entrance 4",
	[TEL5A] = "teleporter entrance 5", [TEL6A] = "teleporter entrance 6",
	[TEL1B] = "teleporter exit 1",	   [TEL2B] = "teleporter exit 2",
	[TEL3B] = "teleporter exit 3",	   [TEL4B] = "teleporter exit 4",
	[TEL5B] = "teleporter exit 5",	   [TEL6B] = "teleporter exit 6",
	[DEAD1] = "dead end 1", [DEAD2] = "dead end 2", [DEAD3] = "dead end 3",
	[DEAD4] = "dead end 4", [DEAD5] = "dead end 5", [DEAD6] = "dead end 6",
	[DEAD7] = "dead end 7", [DEAD8] = "dead end 8", [DEAD9] = "dead end 9"
};

int main(void)
{
	struct Node *node = build_graph1();
	struct Edge **edges;

	int edge_count, i, choice, total;
	char buffer[32];

	edge_count = node->edge_count;
	edges      = node->edges;
	total = 0;

	while (1) {

		printf("current node: %s\noptions (cost):\n",
		       LABELS[node->id]);

		for (i = 0; i < edge_count; ++i) {
			printf("%d. %-25s (%d)\n",
			       i, LABELS[edges[i]->next->id], edges[i]->cost);
		}

		fgets(buffer, sizeof(char) * 4llu, stdin);

		if (buffer[0] == 'q')
			exit(0);

		choice = (int) strtol(buffer, NULL, 10);

		if ((choice < 0) ||
		    (choice >= edge_count)) {
			puts("invalid selection");
			continue;
		}

		total	  += edges[choice]->cost;
		node       = edges[choice]->next;
		edge_count = node->edge_count;

		if (edge_count == 0)
			break;

		edges = node->edges;
	}

	printf("YOU %s!\n\ntotal cost: %d\n",
	       (node->id == GOAL) ? "WIN" : "LOSE", total);

	return 0;
}
