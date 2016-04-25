#include <utils/rand.h>
#include <stddef.h>

void run_grinch(void);

static inline void do_sort(int *data,
			   const ptrdiff_t from,
			   const ptrdiff_t upto);

static inline void swap_ij(int *data,
			   const ptrdiff_t i,
			   const ptrdiff_t j);

ptrdiff_t split_data(int *data,
		     ptrdiff_t from,
		     ptrdiff_t upto);
