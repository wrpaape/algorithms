/*
 * Day       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16
 * Price   100 113 110  85 105 102  86  63  81 101  94 106 101  79  94  90  97
 * Change       13  -3 -25  20  -3 -16 -23  18  20  -7  12  -5  22  15  -4   7
 */

#include <stdio.h>
#include <time.h>
#include <limits.h>

struct SubArrayTup {
	int i_start;
	int i_finish;
	int sum;
};
void max_sub_array(const int *sub_data,
		   const int length,
		   struct SubArrayTup *max_tup)
{

}

void max_between(const int *sub_data,
		 const int length,
		 struct SubArrayTup *max_tup)
{

}

void max_crossing_mid(const int *DATA,
		      const int lenth,
		      struct SubArrayTup *max_tup)
{

	/* struct SubArrayTup *max_tup = malloc(sizeof(struct SubArrayTup)); */

}

int main(void)
{
	int DATA[16] = {
		13,  -3, -25,  20,  -3, -16, -23,  18,
		20,  -7,  12,  -5,  22,  15,  -4,   7
	};

	clock_t time_start;
	clock_t time_stop;
	clock_t time_elapsed;
	struct SubArrayTup max_tup;

	max_tup.sum = INT_MIN;

	time_start = clock();

	max_sub_array(DATA, 16, &max_tup);

	time_stop  = clock();

	time_elapsed = time_stop - time_start;


	printf("%d\n%lu", max_tup.sum, time_elapsed);

	return 0;
}



