#ifndef TSP_USA_SIGNAL_SIGNAL_UTILS_H_
#define TSP_USA_SIGNAL_SIGNAL_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include <signal.h>		/* sig_t, signal */
#include "utils/utils.h"	/* bool, LIKELY, UNLIKELY */


/* API
 * ────────────────────────────────────────────────────────────────────────── */
inline void
signal_muffle(const int name,
	      const sig_t action)
{
	(void) signal(name,
		      action);
}

inline bool
signal_report(const int name,
	      const sig_t action,
	      const char *restrict *const restrict failure)
{
	const bool success = (signal(name,
				     action) != SIG_ERR);

	if (UNLIKELY(!success))
		*failure = "signal failure (one of the following):\n"
			   "\t- 'name' is not a valid signal number.\n"
			   "\t- An attempt was made to ignore or supply a "
			   "handler for 'SIGKILL' or 'SIGSTOP'.\n";

	return success;
}

#endif /* ifndef TSP_USA_SIGNAL_SIGNAL_UTILS_H_ */
