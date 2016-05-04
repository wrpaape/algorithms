#include <gtest/gtest.h>
#include <ctime>

#include "suffix_tree.c"


class SuffixTreeTest : public testing::Test
{
	protected:
		virtual void SetUp() {
			srand((int) time(NULL));
		}

		virtual void TearDown() {
		}
};

/* Tests suffix tree sizing */
TEST_F(SuffixTreeTest, SizeSuffixTree) {

	struct SuffixTreeNodeCount count;
	const char *string = "banana";

	size_suffix_tree(&count, string);

	EXPECT_EQ(3, count.internal);
	EXPECT_EQ(4, count.external);
}
