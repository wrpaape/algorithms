#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* use C linkage */

#include "parenths.h"

/* arbitrary buffer limit */
#define BUFFER_SIZE (sizeof(char) << 10)

/* sized according to worst case (all unmatched parenths) */
#define PRETTY_SIZE (BUFFER_SIZE * (sizeof(ANSI_BLINK)	\
				  + sizeof(ANSI_RED)	\
				  + sizeof('(')		\
				  + sizeof(ANSI_RESET)	\
				  + sizeof(ANSI_BRIGHT)))

#define LENGTH_COLOR_CYCLE 5ul


/* hide the main function during testing */
#ifndef TESTING
int main(void)
{
	char buffer[BUFFER_SIZE];
	char pretty[PRETTY_SIZE];

	struct BalanceScore score;

	fputs("test string for imbalanced parentheses\n"
	      ANSI_BLINK "> " ANSI_BLINK_OFF, stdout);

	fgets(&buffer[0ul], BUFFER_SIZE, stdin);


	process(&score, &pretty[0ul], &buffer[0ul]);

	print_results(&pretty[0ul], &score);

	return 0;
}
#endif

inline void print_results(char *pretty,
			  struct BalanceScore *score)
{
	printf(ANSI_CLEAR ANSI_BRIGHT
	       "%s\n" ANSI_WHITE_BG ANSI_BLUE ANSI_UNDERLINE
	       "RESULTS\n" ANSI_NO_UNDERLINE ANSI_RED
	       "  unmatched '(':  %zu\n"
	       "  unmatched ')':  %zu\n" ANSI_GREEN
	       "  balanced pairs: %zu\n" ANSI_RESET,
	       pretty,
	       score->odd_opened,
	       score->odd_closed,
	       score->even_pairs);
}

void process(struct BalanceScore *score,
	     char *pretty,
	     char *buffer)
{
	size_t even_pairs = 0ul;
	size_t odd_opened = 0ul;
	size_t odd_closed = 0ul;


	struct ColorNode *const cycle = init_color_cycle();
	struct ColorNode *color = cycle;


	struct TokenNode *node;
	struct TokenNode *queue;
	struct TokenNode *stack = NULL;
	struct TokenNode **qtail = &queue;

	struct Token *opened;
	struct Token *closed;
	struct Token *token;

	char *ptr;
	char *parenths;


	for (ptr = buffer; *ptr != '\0'; ++ptr) {

		if (*ptr == '(') {
			opened = init_token(ptr);

			opened->put_prefix = color->put_prefix;

			qtail = enqueue_token(qtail, opened);

			push_token(&stack, opened);

			color = color->next;

			continue;
		}

		if (*ptr == ')') {
			closed = init_token(ptr);

			qtail = enqueue_token(qtail, closed);

			if (stack == NULL) {
				++odd_closed;

				closed->put_prefix = &put_BLINK_RED_prefix;

				continue;
			}

			++even_pairs;

			opened = pop_token(&stack);

			closed->put_prefix = opened->put_prefix;

			color = color->prev;
		}
	}

	free(cycle);

	while (stack != NULL) {
		++odd_opened;

		opened = pop_token(&stack);

		opened->put_prefix = &put_BLINK_RED_prefix;
	}

	*qtail = NULL;


	while (queue != NULL) {

		token = queue->token;

		parenths = token->parenths;

		while (buffer < parenths) {
			*pretty = *buffer;
			++pretty;
			++buffer;
		}

		put_token(&pretty, token);
		++buffer;

		free(token);

		node  = queue;
		queue = queue->link;

		free(node);
	}


	while (*buffer != '\0') {
		*pretty = *buffer;
		++pretty;
		++buffer;
	}


	*pretty = '\0';

	score->even_pairs = even_pairs;
	score->odd_opened = odd_opened;
	score->odd_closed = odd_closed;
}

inline struct TokenNode **enqueue_token(struct TokenNode **qtail,
					struct Token *token)
{
	*qtail = init_token_node();

	(*qtail)->token = token;

	return &(*qtail)->link;
}

inline void push_token(struct TokenNode **stack,
		       struct Token *token)
{
	struct TokenNode *node = init_token_node();

	node->token = token;
	node->link  = *stack;

	*stack = node;
}

inline struct Token *pop_token(struct TokenNode **stack)
{
	struct TokenNode *node = *stack;
	struct Token *token = node->token;

	*stack = node->link;
	free(node);

	return token;
}

inline struct Token *init_token(char *const ptr)
{
	struct Token *token;
	HANDLE_MALLOC(token,
		      struct Token *,
		      sizeof(struct Token));

	token->parenths = ptr;

	return token;
}

inline struct TokenNode *init_token_node(void)
{
	struct TokenNode *node;
	HANDLE_MALLOC(node,
		      struct TokenNode *,
		      sizeof(struct TokenNode));
	return node;
}

inline struct ColorNode *init_color_cycle(void)
{
	struct ColorNode *cycle;
	HANDLE_MALLOC(cycle,
		      struct ColorNode *,
		      sizeof(struct ColorNode) * LENGTH_COLOR_CYCLE);

	/* hook doubly-linked list pointers to form an infinite cycle */
#define SET_NODE(I, FN_PTR)					\
do {								\
	cycle[I].put_prefix = FN_PTR;				\
	cycle[I].prev = &cycle[(I + 4ul) % LENGTH_COLOR_CYCLE];	\
	cycle[I].next = &cycle[(I + 6ul) % LENGTH_COLOR_CYCLE];	\
} while (0)
	SET_NODE(0ul, &put_BLUE_prefix);
	SET_NODE(1ul, &put_CYAN_prefix);
	SET_NODE(2ul, &put_MAGENTA_prefix);
	SET_NODE(3ul, &put_YELLOW_prefix);
	SET_NODE(4ul, &put_WHITE_prefix);
#undef SET_NODE

	return cycle;
}

inline void put_token(char **d_ptr,
		      struct Token *token)
{
	char *ptr = *d_ptr;

	token->put_prefix(&ptr);

	PUT_CHAR(ptr, *(token->parenths));

	PUT_ANSI_RESET(ptr);

	PUT_ANSI_BRIGHT(ptr);

	*d_ptr = ptr;
}

#ifdef __cplusplus
}
#endif /* use C linkage */
