/*
 * Day       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16
 * Price   100 113 110  85 105 102  86  63  81 101  94 106 101  79  94  90  97
 * Change       13  -3 -25  20  -3 -16 -23  18  20  -7  12  -5  22  15  -4   7
 */

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

struct SubArrayTup {
	int start;
	int finish;
	int sum;
};

struct SubArrayTup *max_sub_array(const int *data, const int length);

void max_between(const int *sub_data,
		 const int length,
		 struct SubArrayTup *max_tup);
void max_crossing_mid(const int *mid,
		      const int length_left,
		      const int length_right,
		      struct SubArrayTup *max_tup);

int main(void)
{
	int DATA[16] = {
		13,  -3, -25,  20,  -3, -16, -23,  18,
		20,  -7,  12,  -5,  22,  15,  -4,   7
	};

	clock_t time_start;
	clock_t time_stop;
	clock_t time_elapsed;
	struct SubArrayTup *max_tup;

	time_start = clock();

	max_tup = max_sub_array(DATA, 16);

	time_stop  = clock();

	time_elapsed = time_stop - time_start;


	printf("start:        %d\n"
	       "finish:       %d\n"
	       "max sum:      %d\n"
	       "time_elapsed: %lu\n",
	       max_tup->start, max_tup->finish, max_tup->sum, time_elapsed);

	return 0;
}


struct SubArrayTup *max_sub_array(const int *data, const int length)
{
	struct SubArrayTup *max_tup = malloc(sizeof(struct SubArrayTup));

	max_tup->sum = INT_MIN;

	const int mid = length / 2;

	max_crossing_mid(data, mid, length, max_tup);

	return max_tup;
}

void max_between(const int *sub_data,
		 const int length,
		 struct SubArrayTup *max_tup)
{

}

void max_crossing_mid(const int *data,
		      const int mid,
		      const int length,
		      struct SubArrayTup *max_tup)
{

	int i_max;
	int i;
	int max_sum;
	int sum;

	for (i = mid, sum = 0, max_sum = INT_MIN; i > -1; --i) {
		sum += data[i];
		if (sum > max_sum) {
			max_sum = sum;
			i_max   = i;
		}
	}

	max_tup->start = i_max;
	max_tup->sum	 = max_sum;

	for (i = mid + 1, sum = 0, max_sum = INT_MIN; i < length; ++i) {
		sum += data[i];
		if (sum > max_sum) {
			max_sum = sum;
			i_max   = i;
		}
	}

	max_tup->finish = i_max;
	max_tup->sum   += max_sum;


}









