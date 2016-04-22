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

	const char *literal = ANSI_CYAN "(" ANSI_RESET;

	char buffer[16ul];

	char *ptr = &buffer[0ul];

	put_token(&ptr, &put_CYAN_prefix, '(');

	*ptr = '\0';

	EXPECT_EQ(0, strcmp(literal, buffer));
}

/* Tests proper initialization of doubly-linked color cycle */
TEST_F(ParenthsTest, InitColorCycle) {

	/* space for one cycle's worth of 10 character substrings of the form:
	 *
	 * [ANSI escape prefix] + [token] + [ANSI escape reset]
	 *	   (5ul)	   (1ul)	  (4ul)
	 *
	 * plus a NULL terminator (1ul) */
	static const size_t buffer_size = sizeof(char)
					* ((LENGTH_COLOR_CYCLE * 10ul) + 1ul);

	char buff1[buffer_size];
	char buff2[buffer_size];

	struct ColorNode *init_node;
	struct ColorNode *node;
	char *ptr;
	size_t i;

	struct ColorNode *const cycle = init_color_cycle();

	node = cycle;


	/* test continuity of forward cycle */
	init_node = node;

	ptr = buff1;
	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i, node = node->next)
		put_token(&ptr, node->put_prefix, '(');

	*ptr = '\0';
	ptr  = buff2;

	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i, node = node->next)
		put_token(&ptr, node->put_prefix, '(');

	*ptr = '\0';

	/* stopped where we started? */
	EXPECT_EQ(init_node, node);
	/* generated identical ascending sequences? */
	EXPECT_EQ(0, strcmp(buff1, buff2));


	/* shuffle */
	for (i = (size_t) (rand() % (10 * LENGTH_COLOR_CYCLE)); i > 0ul; --i)
		node = node->prev;

	for (i = (size_t) (rand() % (10 * LENGTH_COLOR_CYCLE)); i > 0ul; --i)
		node = node->next;


	/* test continuity of backward cycle */
	init_node = node;

	ptr = buff1;
	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i, node = node->prev)
		put_token(&ptr, node->put_prefix, ')');

	*ptr = '\0';
	ptr  = buff2;

	for (i = 0ul; i < LENGTH_COLOR_CYCLE; ++i, node = node->prev)
		put_token(&ptr, node->put_prefix, ')');

	/* stopped where we started? */
	EXPECT_EQ(init_node, node);
	/* generated identical descending sequences? */
	EXPECT_EQ(0, strcmp(buff1, buff2));

	free(cycle);
}

