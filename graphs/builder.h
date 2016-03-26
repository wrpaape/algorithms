#ifndef GRAPHS_BUILDER_H_
#define GRAPHS_BUILDER_H_
struct Node *build_graph1(void);
void set_edges(struct Node *node, int *costs, struct Node **next_nodes);
#endif /* ifndef GRAPHS_BUILDER_H_ */
