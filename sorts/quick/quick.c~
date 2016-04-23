#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENGTH_DATA (10ul)

#define PUT_CHAR(PTR, CHAR)	\
do {				\
	*PTR = CHAR;		\
	++PTR;			\
} while (0)

static inline size_t num_digits(const int n)
{
	if (n < 100000) {
		if (n < 1000) {
			if (n < 100)
				return (n < 10) ? 1ul: 2ul;

			return 3ul;
		}

		return (n < 10000) ? 4ul: 5ul;
	}

	if (n < 100000000) {
		if (n < 10000000)
			return (n < 1000000) ? 6ul: 7ul;

		return 8ul;
	}

	return (n < 1000000000) ? 9ul: 10ul;
}

static inline void put_number(char **d_ptr,
			      int n)
{
	const size_t len = num_digits(n);

	char *const base = *d_ptr;

	char *ptr = base + num_digits(n);

	*d_ptr = ptr;

	while (1) {
		--ptr;
		*ptr = (n % 10) + '0';

		if (ptr == base)
			return;

		n /= 10;
	}
}

static inline void put_data(char *ptr,
			    int *data,
			    const size_t length)
{
	PUT_CHAR(ptr, '{');
	put_number(&ptr, data[0l]);

	for (size_t i = 1ul; i < length; ++i) {
		PUT_CHAR(ptr, ','); PUT_CHAR(ptr, ' ');
		put_number(&ptr, data[i]);
	}

	PUT_CHAR(ptr, '}'); PUT_CHAR(ptr, '\0');
}

static inline bool compare(int x,
			   int y)
{
	return x < y;
}

static inline void swap(int *data,
			const size_t i,
			const size_t j)
{
	const int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}


size_t split_data(int *data,
               size_t i,
               size_t j)
{

	size_t i_next = i + 1ul;

	if (i_next == j) {

		if (compare(data[j], data[i]))
			swap(data, i, j);

		return i_next;
	}

	size_t j_next = j - 1ul;

	const size_t i_pivot = i;

	const int pivot = data[i_pivot];

	while (1) {

		while (1) {
			if (i_next == j_next)
				goto PLACE_PIVOT;

			i = i_next;

			++i_next;

			if (compare(pivot, data[i]))
				break;
		}

		while (1) {
			if (compare(data[j], pivot))
				break;

			if (i_next == j_next)
				goto PLACE_PIVOT;


			j = j_next;

			--j_next;
		}

		swap(data, i, j);
	}

PLACE_PIVOT:

	if (compare(pivot, data[i_next])) {

		swap(data, i_pivot, i);
		return j;

	} else {
		swap(data, i_pivot, i_next);
		return i_next;
	}
}

void do_sort(int *data,
	     const size_t i_first,
	     const size_t i_last)
{
	if (i_first < i_last) {

		const size_t i_split = split_data(data, i_first, i_last);

		do_sort(data, i_first,	     i_split - 1ul);
		do_sort(data, i_split + 1ul, i_last);
	}
}



static inline void quick_sort(int *data,
			      const size_t length)
{
	do_sort(data, 0ul, length - 1ul);
}


int main(void)
{
	char raw[LENGTH_DATA * 12ul];
	char sorted[LENGTH_DATA * 12ul];
	int data[LENGTH_DATA];
	time_t dummy;

	srand((unsigned) time(&dummy));

	for (size_t i = 0ul; i < LENGTH_DATA; ++i)
		data[i] = rand() % 100;

	put_data(&raw[0l], data, LENGTH_DATA);

	quick_sort(data, LENGTH_DATA);


	put_data(&sorted[0l], data, LENGTH_DATA);

	printf("raw:\n%s\nsorted:\n%s\n", raw, sorted);

	return 0;
}
