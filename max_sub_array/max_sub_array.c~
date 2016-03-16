/*
 * Day       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16
 * Price   100 113 110  85 105 102  86  63  81 101  94 106 101  79  94  90  97
 * Change       13  -3 -25  20  -3 -16 -23  18  20  -7  12  -5  22  15  -4   7
 */

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct SubArrayTup {
	int start;
	int finish;
	int sum;
};

void max_within(const int *data,
		const int start,
		const int finish,
		struct SubArrayTup *max_tup);
void max_across(const int *data,
		const int start,
		const int mid,
		const int finish,
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
	struct SubArrayTup max_tup;

	time_start = clock();

	max_within(DATA, 0, 15, &max_tup);

	time_stop  = clock();

	time_elapsed = time_stop - time_start;


	printf("start:        %d\n"
	       "finish:       %d\n"
	       "max sum:      %d\n"
	       "time_elapsed: %lu\n",
	       max_tup.start, max_tup.finish, max_tup.sum, time_elapsed);

	return 0;
}


void max_within(const int *data,
		const int start,
		const int finish,
		struct SubArrayTup *max_tup)
{
	if (start == finish) {
		max_tup->start  = start;
		max_tup->finish = finish;
		max_tup->sum	= data[start];
		return;
	}

	struct SubArrayTup max_left;
	struct SubArrayTup max_right;
	struct SubArrayTup max_span;


	const int mid = (start + finish) / 2;

	max_within(data, start,   mid,    &max_left);
	max_within(data, mid + 1, finish, &max_right);
	max_across(data, start, mid, finish, &max_span);

	if (max_left.sum >= max_right.sum &&
	    max_left.sum >= max_span.sum) {

		memcpy(max_tup, &max_left,  sizeof(struct SubArrayTup));

	} else if (max_right.sum >= max_left.sum &&
		   max_right.sum >= max_span.sum) {

		memcpy(max_tup, &max_right, sizeof(struct SubArrayTup));

	} else {
		memcpy(max_tup, &max_span, sizeof(struct SubArrayTup));
	}
}

void max_across(const int *data,
		const int start,
		const int mid,
		const int finish,
		struct SubArrayTup *max_tup)
{

	int i_max;
	int i;
	int max_sum;
	int sum;

	for (i = mid, sum = 0, max_sum = INT_MIN; i >= start; --i) {
		sum += data[i];
		if (sum > max_sum) {
			max_sum = sum;
			i_max   = i;
		}
	}

	max_tup->start = i_max;
	max_tup->sum	 = max_sum;

	for (i = mid + 1, sum = 0, max_sum = INT_MIN; i <= finish; ++i) {
		sum += data[i];
		if (sum > max_sum) {
			max_sum = sum;
			i_max   = i;
		}
	}

	max_tup->finish = i_max;
	max_tup->sum   += max_sum;
}
