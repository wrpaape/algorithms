#ifndef _GRAPHS_MAPS_PATHS_H_
struct Endpoints {
	struct Coords *start;
	struct Coords *goal;
	struct Coords *limits;
};

struct Endpoints *define_endpoints(struct CostMap *map);

inline void free_endpoints(struct Endpoints *pts)
{
	free(pts->start);
	free(pts->goal);
	free(pts->limits);
	free(pts);
}
#define _GRAPHS_MAPS_PATHS_H_
#endif /* ifndef _GRAPHS_MAPS_PATHS_H_ */
