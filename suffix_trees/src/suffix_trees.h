#include <utils/utils.h>

struct Match {
	ptrdiff_t *indices;
	size_t count;
};

struct Match *find_pattern(char *const restrict string,
			   char *const restrict pattern);


inline void free_match(struct Match *match)
{
	free(match->indices);
	free(match);
}
