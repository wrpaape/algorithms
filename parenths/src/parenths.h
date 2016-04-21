#ifndef PARENTHS_H_
#define PARENTHS_H_

#include "token.h"

struct ColorNode {
	void (*put_color_prefix)(char **);
	struct ColorNode *next;
};

struct ParenthsStackNode {
	struct ParenthsStackNode *prev;
};


inline struct ColorNode *init_color_cycle(void);

static inline void put_token(char **d_ptr,
			     void (*put_prefix)(char **),
			     const char token);


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

#define HANDLE_CALLOC(ptr, count, size)					\
do {									\
	ptr = calloc(count, size);					\
	if (ptr == NULL)						\
		EXIT_ON_FAILURE("failed to allocate %lu blocks of %lu"	\
				"bytes", count, size);			\
} while (0)

#define HANDLE_REALLOC(ptr, size)					\
do {									\
	ptr = realloc(ptr, size);					\
	if (ptr == NULL)						\
		EXIT_ON_FAILURE("failed to reallocate memory at '" #ptr	\
				"' to %lu bytes", size);		\
} while (0)

/* macros for defining functions that write ANSI escape sequences to a char
 * pointer before advancing it the length of the write */
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
#undef DEF_PUT_PREFIX1
#undef DEF_PUT_PREFIX2

#endif /* ifndef PARENTHS_H_ */