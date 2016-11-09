#include "signal_utils.h"

/* API
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
signal_muffle(const int name,
	      const sig_t action);
extern inline bool
signal_report(const int name,
	      const sig_t action,
	      const char *restrict *const restrict failure);
