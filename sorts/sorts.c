/************************************************************************************
 *                                     sorts.c                                      *
 *                                                                                  *
 * Module for prototyping and testing basic merge and insertion sorts.              *
 ************************************************************************************/
/************************************************************************************
 *                             PREPROCESSOR DIRECTIVES                              *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 100000
#define PRINT_LENGTH 10
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                             PREPROCESSOR DIRECTIVES                              *
 ************************************************************************************/
/************************************************************************************
 *                               INTIIAL DECLARATIONS                               *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
struct Node {
  int i;
  struct Node *next_ptr;
};
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               INTIIAL DECLARATIONS                               *
 ************************************************************************************/
/************************************************************************************
 *                               FUNCTION PROTOTYPES                                *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
/* top level */
int *insert_sort_by(int *data, int length, int (*sort_by)(const int, const int));
int *merge_sort_by(int *data, int length, int (*sort_by)(const int, const int));
int *select_sort_by(int *data, int length, int (*sort_by)(const int, const int));
/* helper */
int *shuffle(int *dest, int *data, int length);
int rand_btwn_inc(const int min, const int max);
int desc(const int x, const int y);
int asc(const int x, const int y);
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               FUNCTION PROTOTYPES                                *
 ************************************************************************************/
/************************************************************************************
 *                                  MAIN FUNCTION                                   *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
int main(void)
{

  int asc_data[LENGTH];                 /* data in ascending order:  0..(N - 1) */
  int desc_data[LENGTH];                /* data in descending order: (N - 1)..0 */
  int shuf_data[LENGTH];                /* shuffled data composed of same range */
  int data[LENGTH];                     /* */
  int data_insert[LENGTH];              /* identical copy */
  int data_merge[LENGTH];               /* identical copy */
  int data_select[LENGTH];              /* identical copy */
  int (*sort_by)(const int, const int); /* pointer to sorting condition */
  clock_t time_insert;
  clock_t time_merge;
  clock_t time_select;
  int i;                                /* generic counter */




  for (i = 0; i < LENGTH; ++i) {
    asc_data[i] = i;
    desc_data[i] = LENGTH - i;
    shuf_data[i]   = rand();
    data_insert[i] = rand_data[i];
    data_merge[i]  = data_insert[i];
    data_select[i] = data_merge[i];
  }

  for (i = 0; i < LENGTH; ++i) {
    asc_data[i] = i;
    desc_data[i] = LENGTH - i;
  }



  sort_by = &desc;


  printf("sort by: %s order\n\n", (sort_by == asc) ? "ASCENDING" : "DESCENDING");

  /* time insertion sort */
  fputs("timing insertion sort...", stdout);
  time_insert = clock();
  insert_sort_by(LENGTH, data_insert, sort_by);
  time_insert = clock() - time_insert;
  fputs("done\n", stdout);


  /* time merge sort */
  fputs("timing merge sort...", stdout);
  time_merge = clock();
  merge_sort_by(LENGTH, data_merge, sort_by);
  time_merge = clock() - time_merge;
  fputs("done\n", stdout);

  /* time selection sort */
  fputs("timing selection sort...", stdout);
  time_select = clock();
  select_sort_by(LENGTH, data_select, sort_by);
  time_select = clock() - time_select;
  fputs("done\n", stdout);


  printf("\nN:         %i\ninsertion: %lu μs\nmerge:     %lu μs\nselection: %lu μs\n\n",
      LENGTH, time_insert, time_merge, time_select);

  puts(" unsorted  ┃ insertion  ┃   merge    ┃ selection\n"
       "━━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━ ");
  for (i = 0; i < PRINT_LENGTH; ++i) {
    printf("%-10i ┃ %-10i ┃ %-10i ┃ %-10i\n",
        data[i], data_insert[i], data_merge[i], data_select[i]); 
  }
  puts("     ⋮     ┃      ⋮     ┃      ⋮     ┃     ⋮");

  for (i = LENGTH - PRINT_LENGTH; i < LENGTH; ++i) {
    printf("%-10i ┃ %-10i ┃ %-10i ┃ %-10i\n",
        data[i], data_insert[i], data_merge[i], data_select[i]); 
  }
  
  return 0;
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                                  MAIN FUNCTION                                   *
 ************************************************************************************/
/************************************************************************************
 *                               TOP LEVEL FUNCTIONS                                *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
int *insert_sort_by(int *data, int length, int (*sort_by)(const int, const int))
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

int *merge_sort_by(int *data, int length, int (*sort_by)(const int, const int))
{

  return data;
}


int *select_sort_by(int *data, int length, int (*sort_by)(const int, const int))
{
  int sort_range;
  int j;
  int head;
  int head_index;

  sort_range = length - 1;

  for (int i = 0; i < sort_range; ++i) {
    head_index = i;
    head       = data[head_index];

    for (j = i + 1; j < length; ++j) {
      if (sort_by(data[j], head)) {
        head_index = j;
        head = data[head_index];
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
int *shuffle(int *dest, int *data, int length)
{
  srand(time(NULL)); /* seed RNG */

  return dest;
}


int rand_btwn_inc(const int min, const int max)
{
  int value;


  return value;
}


int desc(const int x, const int y)
{
  return (x > y);
}


int asc(const int x, const int y)
{
  return (x < y);
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                                 HELPER FUNCTIONS                                 *
 ************************************************************************************/
