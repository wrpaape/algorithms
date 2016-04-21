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

static inline void put_color_token(char **d_ptr,
				   void (*put_ansi)(char **),
				   const char token);

#define DEFINE_ANSI_PUT_FUNCTION(ANSI_TOKEN)	\
void put_ ## ANSI_TOKEN(char **d_ptr) {		\
	char *ptr = *d_ptr;			\
	PUT_ANSI_ ## ANSI_TOKEN(ptr);		\
	*d_ptr = ptr;				\
}

DEFINE_ANSI_PUT_FUNCTION(RED)

#endif /* ifndef PARENTHS_H_ */
