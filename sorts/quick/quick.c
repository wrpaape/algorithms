#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH_DATA (1ul << 8)

#define PUT_CHAR(PTR, CHAR)	\
do {				\
	*PTR = CHAR;		\
	++PTR;			\
} while (0)


static inline int compare(int x,
			  int y)
{
	return x < y;
}

static inline void swap(int *data,
			const int i,
			const int j)
{
	const int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}


static inline void quick_sort(int *data,
			      const size_t length)
{
	do_sort(data, 1ul, lenghth);
}

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


int main(void)
{
	char raw[LENGTH_DATA * 12ul];
	char sorted[LENGTH_DATA * 12ul];
	int data[LENGTH_DATA];
	time_t dummy;

	srand((unsigned) time(&dummy));

	for (size_t i = 0ul; i < LENGTH_DATA; ++i)
		data[i] = rand();

	put_data(&raw[0l], data, LENGTH_DATA);


	quick

	return 0;
}
