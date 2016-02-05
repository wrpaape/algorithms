/************************************************************************************
 *                                     sorts.c                                      *
 *                                                                                  *
 * Module for prototyping basic merge, insertion, and selection sorts.              *
 ************************************************************************************/
/************************************************************************************
 *                             PREPROCESSOR DIRECTIVES                              *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
#include "sorts.h"
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                             PREPROCESSOR DIRECTIVES                              *
 ************************************************************************************/
/************************************************************************************
 *                                  MAIN FUNCTION                                   *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
int main(void)
{
  /* args for insertion, merger, and selection sort */
  struct SortAlg sort_algs[] = {{.alg_func = insert_sort_by,
                               .alg_name = "INSERTION",
                               .test_ords = {{.init_ord = "ASCENDING"},
                                             {.init_ord = "DESCENDING"},
                                             {.init_ord = "SHUFFLED"}}},
                              {.alg_func = merge_sort_by,
                               .alg_name = "MERGE"},
                              {.alg_func = select_sort_by,
                               .alg_name = "SELECTION"}};


  /* initialize common data */
  int i; /* generic counter */

  for (i = 0; i < LENGTH; ++i) {
    sort_algs[0].test_ords[0].test_dirs[0].data[i] = i;          /* asc_ord order:  0..(N - 1) */
    sort_algs[0].test_ords[1].test_dirs[0].data[i] = LENGTH - i; /* desc_ord order: (N - 1)..0 */
    sort_algs[0].test_ords[2].test_dirs[0].data[i] = i;          /* shuffled order */
  }

  shuffle(sort_algs[0].test_ords[2].test_dirs[0].data, LENGTH); /* shuffle data */

  /* assign name strings and copy data from 'ASCENDING' to 'DESCENDING' test dir */ 
  for (i = 0; i < ORDS_PER_ALG; ++i) {
    sort_algs[0].test_ords[i].test_dirs[0].sort_by = &asc_ord;
    sort_algs[0].test_ords[i].test_dirs[1].sort_by = &desc_ord;

    strcpy(sort_algs[0].test_ords[i].test_dirs[0].sort_dir, "ASCENDING");
    strcpy(sort_algs[0].test_ords[i].test_dirs[1].sort_dir, "DESCENDING");

    memcpy(sort_algs[0].test_ords[i].test_dirs[1].data,
           sort_algs[0].test_ords[i].test_dirs[0].data,
           SIZE_DATA);
  }

  /* copy test data to remaining sorts */
  for (i = 1; i < NUM_ALGS; ++i) {
    memcpy(sort_algs[i].test_ords,
           sort_algs[0].test_ords,
           SIZE_ORDS);
  }

  /* test sorting algorithms */

  test_algs(sort_algs, NUM_ALGS);

  /* report results */

  report(sort_algs, NUM_ALGS);
  
  return 0;
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                                  MAIN FUNCTION                                   *
 ************************************************************************************/
/************************************************************************************
 *                               TOP LEVEL FUNCTIONS                                *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
int *insert_sort_by(int *data, const size_t length, int (*sort_by)(const int, const int))
{
  int temp;
  int j;

  for (int i = 1; i < length; ++i) {
    temp = data[i];
    j = i - 1;
    
   /* if current el should be ordered ahead of next previous el */
    while ((j > -1) && sort_by(temp, data[j])) {
      /* shift next previous el forward, making room for current el */
      data[j + 1] = data[j];
      --j;
    }

    /* drop current el into its proper position */
    data[j + 1] = temp;
  }

  return data;
}

int *merge_sort_by(int *data, const size_t length, int (*sort_by)(const int, const int))
{

  return data;
}


int *select_sort_by(int *data, const size_t length, int (*sort_by)(const int, const int))
{
  int sort_range;
  int i;
  int j;
  int head;
  int head_index;

  sort_range = length - 1;

  for (i = 0; i < sort_range; ++i) {
    head_index = i;
    head       = data[head_index];

    for (j = i + 1; j < length; ++j) {
      if (sort_by(data[j], head)) {
        head_index = j;
        head       = data[head_index];
      }
    }

    data[head_index] = data[i];
    data[i]          = head;
  }

  return data;
}


/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               TOP LEVEL FUNCTIONS                                *
 ************************************************************************************/
/************************************************************************************
 *                                 HELPER FUNCTIONS                                 *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
int desc_ord(const int el1, const int el2)
{
  return (el1 > el2);
}


int asc_ord(const int el1, const int el2)
{
  return (el1 < el2);
}
