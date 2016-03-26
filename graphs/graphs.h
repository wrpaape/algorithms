#ifndef GRAPHS_H_
#define GRAPHS_H_ value
#include <stdlib.h>	/* malloc, free, exit */
#include <stdio.h>	/* fprintf, printf */
#include <errno.h>	/* errno */
#include <string.h>	/* strerror */
#include <limits.h>	/* max word value */

#define EXIT_ON_FAILURE(format, ...)					\
do {									\
	fprintf(stderr,							\
		"\n\e[31m\e[5mERROR:\e[25m\t\e[4m" format "\e[24m\n\n"	\
		"errno:\t%s\n\n"					\
		"file:\t%s\n\n"						\
		"func:\t%s\n\n"						\
		"line:\t%d\e[0m\n",					\
		##__VA_ARGS__,						\
		strerror(errno), __FILE__, __func__, __LINE__);		\
	exit(EXIT_FAILURE);						\
} while (0)

#define HANDLE_MALLOC(ptr, size)					\
do {									\
	ptr = malloc(size);						\
	if (ptr == NULL)						\
		EXIT_ON_FAILURE("failed to allocate %lu bytes", size);	\
} while (0)

#define INIT(NODE, ID, EDGE_COUNT)					\
do {									\
	HANDLE_MALLOC(NODE, sizeof(struct Node));			\
	NODE->id	  = ID;						\
	NODE->edge_count  = EDGE_COUNT;					\
	if (EDGE_COUNT > 0) {						\
		HANDLE_MALLOC(NODE->edges,				\
			      sizeof(struct Edge*) * EDGE_COUNT);	\
	} else {							\
		NODE->edges = NULL;					\
	}								\
} while (0)


#define WRAP(...) __VA_ARGS__

#define SET_EDGES(NODE, COSTS, NEXTS)					\
do {									\
	int costs[] = COSTS;						\
	struct Node *nexts[] = NEXTS;					\
	set_edges(NODE, costs, nexts);					\
} while (0)

#define TELEPORT_COST 5


enum NodeID {
	START, GOAL,
	NODE1, NODE2, NODE3, NODE4, NODE5, NODE6, NODE7,
	TEL1A, TEL2A, TEL3A, TEL4A, TEL5A, TEL6A,
	TEL1B, TEL2B, TEL3B, TEL4B, TEL5B, TEL6B,
	DEAD1, DEAD2, DEAD3, DEAD4, DEAD5, DEAD6, DEAD7, DEAD8, DEAD9
};

struct Node {
	enum NodeID id;
	int edge_count;
	struct Edge **edges;
};

struct Edge {
	int cost;
	struct Node *next;
};

const char *NODE_LABELS[] = {
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

struct Node *init_graph(void);
void set_edges(struct Node *node, int *costs, struct Node **next_nodes);
#endif /* ifndef GRAPHS_H_ */
