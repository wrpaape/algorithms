#include <stdio.h>
#include <stddef.h>
#include <assert.h>


void
swap(int *const restrict array,
     const size_t i,
     const size_t j)
{
    int *const restrict array_i = &array[i];
    int *const restrict array_j = &array[j];

    const int tmp = *array_i;
    *array_i = *array_j;
    *array_j = tmp;
}


size_t
do_split(int *const restrict array,
         size_t i_from,
         size_t i_upto)
{
    const size_t i_split = i_from;
    const int split = array[i_split];

    ++i_from;

    if (i_from == i_upto) {
        if (array[i_from] < split)
            swap(array,
                 i_split,
                 i_from);

        return i_from;
    }


    while (1) {
        while (array[i_from] <= split) {
            ++i_from;

            if (i_from == i_upto) {
                if (array[i_from] > split)
                    --i_from;

                swap(array,
                     i_split,
                     i_from);

                return i_from;
            }
        }

        while (array[i_upto] >= split) {
            --i_upto;

            if (i_from == i_upto) {
                --i_from;

                swap(array,
                     i_split,
                     i_from);

                return i_from;
            }
        }


        swap(array,
             i_from,
             i_upto);

        ++i_from;

        if (i_from == i_upto) {
            --i_from;

            swap(array,
                 i_split,
                 i_from);

            return i_from;
        }

        --i_upto;

        if (i_from == i_upto) {
            if (array[i_from] > split)
                --i_from;

            swap(array,
                 i_split,
                 i_from);

            return i_from;
        }
    }
}

int
do_nth_smallest(int *const restrict array,
                const size_t i_from,
                const size_t i_upto,
                const size_t n)
{
    if (i_from < i_upto) {
        const size_t i_split = do_split(array,
                                        i_from,
                                        i_upto);

        return (i_split < n)
             ? do_nth_smallest(array,
                               i_split + 1,
                               i_upto,
			       n)
             : (i_split > n)
             ? do_nth_smallest(array,
                               i_from,
                               i_split - 1,
			       n)
             : array[i_split];

    } else {
        return array[i_from];
    }
}




int
nth_smallest(int *const restrict result,
             int *const restrict array,
             const size_t length,
             const size_t n)
{

    const int can_find = (n > 0) && (n <= length);

    if (can_find)
        *result = do_nth_smallest(array,
                                  0,
                                  length - 1,
                                  n - 1);

    return can_find;
}

int
main(void)
{
	int array[10] = {
		9, 3, 10, 3, 2, 1, 8, 7, 5, 6
	};

	int result;

	assert(nth_smallest(&result,
			    &array[0],
			    10,
			    1));

	printf("%d smallest: %d\n", 1, result);

	assert(!nth_smallest(&result,
			     &array[0],
			     10,
			     11));

	assert(nth_smallest(&result,
			    &array[0],
			    10,
			    7));

	printf("%d smallest: %d\n", 7, result);


	return 0;
}
