#include <gtest/gtest.h>
#include <ctime>

#include "suffix_tree.c"

#define LOREM								\
"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do "	\
"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "	\
"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "	\
"aliquip ex ea commodo consequat. Duis aute irure dolor in "		\
"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "	\
"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "	\
"culpa qui officia deserunt mollit anim id est laborum."



class SuffixTreeTest : public testing::Test
{
	protected:
		virtual void SetUp() {
			srand((int) time(NULL));
		}

		virtual void TearDown() {
		}
};

/* Tests function 'size_suffix_tree' */
TEST_F(SuffixTreeTest, SizeSuffixTree) {

	/*	    │ "banana" │ "aaaaaa" |  ""
	 * ─────────┼──────────┼──────────┼───────
	 *	 1. │   'b'    │   'a'	  │ '\0'
	 * 	 2. │   'a'    │   'a'    │
	 * 	 3. │   'n'    │   'a'    │
	 * 	 4. │   'a'    │   'a'    │
	 * 	 5. │   'n'    │   'a'    │
	 * 	 6. │   'a'    │   'a'    │
	 * 	 7. │   '\0'   │   '\0'   │
	 * ─────────┼──────────┼──────────┼───────
	 * length   │    7     │    7     │  1
	 * ─────────┼──────────┼──────────┼───────
	 * alphabet │    4     │    2     │  1
	 * size     │          │          │
	 * ─────────┼──────────┼──────────┼───────
	 * external │          │          │
	 * nodes =  │    7     │    7     │  1
	 * length   │          │          │
	 * ─────────┼──────────┼──────────┼───────
	 * internal │          │          │
	 * nodes =  │  7 - 4   │  7 - 2   │ 1 - 1
	 * external │    =     │    =     │   =
	 * nodes -  │    3     │    5     │   0
	 * length   │          │          │       */

	struct SuffixTreeNodeCount count;

	size_suffix_tree(&count, "banana");
	EXPECT_EQ(7, count.external);
	EXPECT_EQ(3, count.internal);

	size_suffix_tree(&count, "aaaaaa");
	EXPECT_EQ(7, count.external);
	EXPECT_EQ(5, count.internal);

	size_suffix_tree(&count, "");
	EXPECT_EQ(1, count.external);
	EXPECT_EQ(0, count.internal);
}

/* Tests function 'build_suffix_tree' */
TEST_F(SuffixTreeTest, BuildSuffixTree) {

	struct SuffixTree *tree = build_suffix_tree("abc");

	struct SuffixNode **edge_map  = tree->root_map;


	EXPECT_NE(nullptr, CHAR_GET(edge_map, 'a'));
	EXPECT_NE(nullptr, CHAR_GET(edge_map, 'b'));
	EXPECT_NE(nullptr, CHAR_GET(edge_map, 'c'));
	EXPECT_NE(nullptr, CHAR_GET(edge_map, '\0'));

	free(tree);
}

/* Tests function 'rem_match_contains' */
TEST_F(SuffixTreeTest, RemMatchContains) {

	EXPECT_TRUE(rem_match_contains("abc", "ab"));
	EXPECT_TRUE(rem_match_contains("abc", ""));

	EXPECT_FALSE(rem_match_contains("abc", "bc"));

	EXPECT_FALSE(rem_match_contains("ab", "abc"));
	EXPECT_FALSE(rem_match_contains("bc", "abc"));
	EXPECT_FALSE(rem_match_contains("",   "abc"));
}



/* Tests function 'string_contains' */
TEST_F(SuffixTreeTest, StringContains) {

	EXPECT_TRUE(string_contains("abc", "ab"));
	EXPECT_TRUE(string_contains("abc", ""));

	EXPECT_TRUE(string_contains("abc", "bc"));

	EXPECT_FALSE(string_contains("ab", "abc"));
	EXPECT_FALSE(string_contains("bc", "abc"));
	EXPECT_FALSE(string_contains("",   "abc"));

	EXPECT_TRUE(string_contains(LOREM,  "cillum"));
	EXPECT_FALSE(string_contains(LOREM, "cillym"));

}
