/************************************************************************************
 *                                     sorts.h                                      *
 *                                                                                  *
 * Header file for 'sorts.c', a module for prototyping and testing basic merge,     *
 * insertion and selection sorts.                                                   *
 ************************************************************************************/
/************************************************************************************
 *                             PREPROCESSOR DIRECTIVES                              *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                             PREPROCESSOR DIRECTIVES                              *
 ************************************************************************************/
/************************************************************************************
 *                               FUNCTION PROTOTYPES                                *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
/* top level */
int *insert_sort_by(int *data, const size_t length,
    int (*sort_by)(const int el1, const int el2));
int *merge_sort_by( int *data, const size_t length,
    int (*sort_by)(const int el1, const int el2));
int *select_sort_by(int *data, const size_t length,
    int (*sort_by)(const int el1, const int el2));
/* helper */
void do_split(int *data, const size_t i_start, const size_t i_end,
    int (*sort_by)(const int, const int), const int sentinel);
void merge(int *data, const size_t i_start, const size_t i_split, const size_t i_end,
    int (*sort_by)(const int, const int), const int sentinel);
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               FUNCTION PROTOTYPES                                *
 ************************************************************************************/
