#include <gtest/gtest.h>
#include <ctime>

/* hide main */
#define TESTING
#include "parenths.c"



class ParenthsTest : public testing::Test
{
	protected:
		virtual void SetUp() {
			srand((int) time(NULL));
		}

		virtual void TearDown() {
		}
};

/* Tests 'put_token' function */
TEST_F(ParenthsTest, PutColorToken) {

	const char *literal = ANSI_CYAN "(" ANSI_RESET ANSI_BRIGHT;

	char buffer[16ul];

	char *ptr = &buffer[0ul];

	char parenths = '(';

	struct Token token = {
		.parenths   = &parenths,
		.put_prefix = &put_CYAN_prefix
	};

	put_token(&ptr, &token);

	*ptr = '\0';

	EXPECT_EQ(0, strcmp(literal, buffer));
}

/* Tests proper initialization of doubly-linked color cycle */
TEST_F(ParenthsTest, InitColorCycle) {

	/* space for one cycle's worth of 14 character substrings of the form:
	 *
	 * [ANSI prefix] + [token] + [ANSI reset] + [ANSI bright]
	 *     (5ul)	    (1ul)	 (4ul)	       (4ul)
	 *
	 * plus a NULL terminator (1ul) */
	static const size_t buffer_size = sizeof(char)
					* ((LENGTH_COLOR_CYCLE * 14ul) + 1ul);

	char buff1[buffer_size];
	char buff2[buffer_size];

	struct ColorNode *init_node;
	struct ColorNode *node;
	char parenths = '(';
	struct Token token = {
		.parenths = &parenths
	};

	char *ptr;
	size_t i;

	struct ColorNode *const cycle = init_color_cycle();
	node = cycle;


	/* test continuity of forward cycle */
	init_node = node;
	ptr = buff1;
	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i) {
		token.put_prefix = node->put_prefix;
		put_token(&ptr, &token);
		node = node->next;
	}
	*ptr = '\0';
	ptr  = buff2;
	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i) {
		token.put_prefix = node->put_prefix;
		put_token(&ptr, &token);
		node = node->next;
	}
	*ptr = '\0';

	EXPECT_EQ(init_node, node);	    // stopped where we started?
	EXPECT_EQ(0, strcmp(buff1, buff2)); // identical ascending sequences?


	/* shuffle */
	for (i = (size_t) (rand() % (10 * LENGTH_COLOR_CYCLE)); i > 0ul; --i)
		node = (rand() & 1) ? node->prev : node->next;


	/* test continuity of backward cycle */
	init_node = node;
	ptr = buff1;
	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i) {
		token.put_prefix = node->put_prefix;
		put_token(&ptr, &token);
		node = node->prev;
	}
	*ptr = '\0';
	ptr  = buff2;
	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i) {
		token.put_prefix = node->put_prefix;
		put_token(&ptr, &token);
		node = node->prev;
	}
	*ptr = '\0';

	EXPECT_EQ(init_node, node);	    // stopped where we started?
	EXPECT_EQ(0, strcmp(buff1, buff2)); // identical descending sequences?

	free(cycle);
}

