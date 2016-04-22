#ifndef PARENTHS_H_
#define PARENTHS_H_

#include <stdlib.h>	/* malloc, free, exit, size_t */
#include <stddef.h>	/* ptrdiff_t */
#include <stdio.h>	/* printf, fprintf */
#include <errno.h>	/* errno */
#include <string.h>	/* strerror */
#include "token.h"	/* ANSI escape sequence put macros */

struct Token {
	char parenths;
	void (*put_prefix)(char **);
};

struct TokenNode {
	struct Token *token;
	struct TokenNode *link;
};

struct ColorNode {
	void (*put_prefix)(char **);
	struct ColorNode *prev;
	struct ColorNode *next;
};

struct BalanceScore {
	size_t even_pairs;
	size_t odd_opened;
	size_t odd_closed;
};

void process(struct BalanceScore *score,
	     char *__restrict__ pretty,
	     char *__restrict__ buffer);

static inline void print_score(struct BalanceScore *score);

static inline struct TokenNode *init_token_node(void);
static inline struct IntervalNode *init_interval_node(void);
static inline struct ColorNode *init_color_cycle(void);

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


#ifdef __cplusplus /* provide type and cast return for c++ */
#define HANDLE_MALLOC(PTR, PTR_TYPE, SIZE)				\
do {									\
	PTR = (PTR_TYPE) malloc(SIZE);					\
	if (PTR == NULL)						\
		EXIT_ON_FAILURE("failed to allocate %lu bytes", SIZE);	\
} while (0)
#else /* leave uncasted by default */
#define HANDLE_MALLOC(PTR, PTR_TYPE, SIZE)				\
do {									\
	PTR = malloc(SIZE);						\
	if (PTR == NULL)						\
		EXIT_ON_FAILURE("failed to allocate %lu bytes", SIZE);	\
} while (0)
#endif

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
DEF_PUT_PREFIX1(BLUE)
DEF_PUT_PREFIX1(CYAN)
DEF_PUT_PREFIX1(MAGENTA)
DEF_PUT_PREFIX1(YELLOW)
DEF_PUT_PREFIX1(WHITE)
DEF_PUT_PREFIX2(BLINK, RED)
#undef DEF_PUT_PREFIX1
#undef DEF_PUT_PREFIX2

#endif /* ifndef PARENTHS_H_ */
