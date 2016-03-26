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
	HANDLE_MALLOC(NODE->edges, sizeof(struct Edge) * EDGE_COUNT);	\
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
	struct Edge *edges;
};

struct Edge {
	int cost;
	struct Node *next;
};


struct Node *init_graph(void);
#endif /* ifndef GRAPHS_H_ */
