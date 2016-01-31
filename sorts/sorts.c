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

#define LENGTH 1000
#define PRINT_LENGTH 10
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                             PREPROCESSOR DIRECTIVES                              *
 ************************************************************************************/
/************************************************************************************
 *                               FUNCTION PROTOTYPES                                *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
int *insert_sort_by(int length, int *data, int (*sort_by)(const int, const int));
int *merge_sort_by(int length, int *data, int (*sort_by)(const int, const int));
int *select_sort_by(int length, int *data, int (*sort_by)(const int, const int));
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
  int data[LENGTH];                     /* data to be sorted */
  int data_insert[LENGTH];              /* identical copy */
  int data_merge[LENGTH];               /* identical copy */
  int data_select[LENGTH];              /* identical copy */
  int (*sort_by)(const int, const int); /* pointer to sorting condition */
  clock_t time_insert;
  clock_t time_merge;
  clock_t time_select;
  int i;                                /* generic counter */

  srand(time(NULL));                    /* seed RNG */

  for (i = 0; i < LENGTH; ++i) {
    data[i]        = rand();
    data_insert[i] = data[i];
    data_merge[i]  = data_insert[i];
    data_select[i] = data_merge[i];
  }

  sort_by = &desc;


  printf("sort by: %s order\n\n", (sort_by == asc) ? "ASCENDING" : "DESCENDING");

  /* time insertion sort */
  puts("timing insertion sort...");
  time_insert = clock();
  insert_sort_by(LENGTH, data_insert, sort_by);
  time_insert = clock() - time_insert;
  puts("done\n");


  /* time merge sort */
  puts("timing merge sort...");
  time_merge = clock();
  merge_sort_by(LENGTH, data_merge, sort_by);
  time_merge = clock() - time_merge;
  puts("done\n");

  /* time selection sort */
  puts("timing selection sort...");
  time_select = clock();
  select_sort_by(LENGTH, data_select, sort_by);
  time_select = clock() - time_select;
  puts("done\n");


  printf("N:      %i\ninsert: %lu μs\nmerge:  %lu μs\nselect: %lu μs\n\n",
      LENGTH, time_insert, time_merge, time_select);

  puts("unsorted       ┃ insertion sort ┃ merge sort     ┃ selection sort");
  puts("━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━ ");
  for (i = 0; i < PRINT_LENGTH; ++i) {
    printf("%-14i ┃ %-14i ┃ %-14i ┃ %-14i\n",
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
int *insert_sort_by(int length, int *data, int (*sort_by)(const int, const int))
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

int *merge_sort_by(int length, int *data, int (*sort_by)(const int, const int))
{

  return data;
}


int *select_sort_by(int length, int *data, int (*sort_by)(const int, const int))
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

int desc(const int x, const int y)
{
  return (x > y);
}

int asc(const int x, const int y)
{
  return (x < y);
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               TOP LEVEL FUNCTIONS                                *
 ************************************************************************************/
