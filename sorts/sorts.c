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
  /* determine sentinel value ("least" value according to sort_by) */
  const int sent = sort_by(INT_MIN, INT_MAX) ? INT_MIN : INT_MAX;

  do_split(data, 0, length - 1, sort_by, sent)

  return data;
}

void do_split(int *data, const size_t i_start, const size_t i_end, int (*sort_by)(const int, const int), const int sent)
{
  /* if sub-array is longer than 1 element, recurse */
  if (i_start < i_end) {
    /* split current sub-array into left and right sub-sub-arrays */
    int i_split;
    i_split = (i_end - i_start) / 2;

    do_split(data, i_start,     i_split, sort_by); /* sort left sub-sub-array */
    do_split(data, i_split + 1, i_end,   sort_by); /* sort right sub-sub-array */
    merge(data, i_start, i_split, i_end, sort_by); /* merge sorted sub-sub-arrays */
  }
}

void merge(int *data, const size_t i_start, const size_t i_split, const size_t i_end, int (*sort_by)(const int, const int), const int sent)
{
  size_t i_left;
  size_t i_right;
  size_t i_merge;
  size_t copy_cutoff;
  size_t length_left_arr;
  size_t length_right_arr;
  int *left_sub;
  int *right_sub;

  const size_t i_start_right = i_split + 1;

  length_left_arr  = i_split - i_start       + 2;
  length_right_arr = i_end   - i_start_right + 2;

  left_sub  = (int *) malloc(sizeof(int) * length_left_arr);
  right_sub = (int *) malloc(sizeof(int) * length_right_arr);

  /* copy right sub-array data to 'right_sub' */
  copy_cutoff = length_left_arr - 1;
  for (i_left = 0; i_left < copy_cutoff; ++i_left) {
    left_sub[i_left] = data[i_start + i_left];
  }
  left_sub[i_left] = last_val;  /* append sentinel value */

  /* copy right sub-array data to 'right_sub' */
  copy_cutoff = length_right_arr - 1;
  for (i_right = 0; i_right < copy_cutoff; ++i_right) {
    right_sub[i_right] = data[i_start_right + i_right];
  }
  right_sub[i] = last_val; /* append sentinel value */

  i_left  = i_start;
  i_right = i_start_right;

  for (i_merge = i_start; i_merge < i_end; ++i_merge) {
    if (sort_by(left_sub[i_left], right_sub[i_right])) {
      
    } else {
      
    }
    
  }



  /* free(left_sub); */
  /* free(right_sub); */
}

int *select_sort_by(int *data, const size_t length, int (*sort_by)(const int, const int))
{
  size_t sort_range;
  size_t i;
  size_t j;
  size_t head;
  size_t head_index;

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
