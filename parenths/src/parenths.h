#ifndef PARENTHS_H_
#define PARENTHS_H_

#include <stdbool.h>
#include "token.h"

struct ColorNode {
	char *code;
};

struct ParenthsStackNode {
	struct ParenthsStackNode *prev;
};

static inline void put_token(char **d_ptr,
			     void (*put_prefix)(char **),
			     const char token);

static inline void put_ERROR_prefix(char **d_ptr);

#define DEF_PUT_PREFIX1(TYPE)						\
static inline void put_ ## TYPE ## _prefix(char **d_ptr)		\
{									\
	char *ptr = *d_ptr;						\
	PUT_ANSI_ ## TYPE(ptr);						\
	*d_ptr = ptr;							\
}
#define DEF_PUT_PREFIX2(TYPE1, TYPE2)					\
static inline void put_ ## TYPE1 ## _ ## TYPE2 ## _prefix(char **d_ptr)	\
{									\
	char *ptr = *d_ptr;						\
	PUT_ANSI_ ## TYPE1(ptr);					\
	PUT_ANSI_ ## TYPE2(ptr);					\
	*d_ptr = ptr;							\
}

DEF_PUT_PREFIX1(MAGENTA)
DEF_PUT_PREFIX1(YELLOW)
DEF_PUT_PREFIX1(BLUE)
DEF_PUT_PREFIX1(CYAN)
DEF_PUT_PREFIX1(WHITE)
DEF_PUT_PREFIX2(BLINK, RED)

#endif /* ifndef PARENTHS_H_ */
