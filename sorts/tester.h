/************************************************************************************
 *                                     tester.h                                     *
 *                                                                                  *
 * Header file for 'tester.c', a module for testing basic merge and insertion       *
 * sorts.                                                                           *
 ************************************************************************************/
/************************************************************************************
 *                             PREPROCESSOR DIRECTIVES                              *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "sorts.h"

#define BUFFER_SIZE 20
#define LENGTH 10
#define PRINT_LENGTH 10
#define NUM_ALGS 3
#define ORDS_PER_ALG 3
#define DIRS_PER_ORD 2
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                             PREPROCESSOR DIRECTIVES                              *
 ************************************************************************************/
/************************************************************************************
 *                               INTIIAL DECLARATIONS                               *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
struct TestDir {
  int (*sort_by)(const int el1, const int el2); /* pointer to sorting condition */
  char sort_dir[BUFFER_SIZE]; /* sort direction */
  int data[LENGTH];           /* positive ints in particular order */
  clock_t sort_time;          /* time elapsed sorting data */
};

struct TestOrd {
  char init_ord[BUFFER_SIZE];       /* initial data order */
  struct TestDir test_dirs[DIRS_PER_ORD]; /* holds initial data and place for time result */
};

struct SortAlg {
  int *(*alg_func)(int *data, const size_t length, /* pointer to sorting function */
      int (*sort_by)(const int el1, const int el2));
  char alg_name[BUFFER_SIZE];                  /* sorting algorithm */
  struct TestOrd test_ords[ORDS_PER_ALG];    /* test orders */
};

const size_t SIZE_DATA = sizeof(((struct TestDir *) NULL) -> data);
const size_t SIZE_ORDS = sizeof(((struct SortAlg *) NULL) -> test_ords);
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               INTIIAL DECLARATIONS                               *
 ************************************************************************************/
/************************************************************************************
 *                               FUNCTION PROTOTYPES                                *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
/* top level */
void test_algs(struct SortAlg *alg_ptr, const size_t length);
void report(struct SortAlg *algs, const size_t num_algs);

/* helper */
char **build_lines(const size_t line_width, const size_t col_width, const size_t num_cols);
int *shuffle(int *data, const unsigned long long length);
unsigned long long rand_upto(const unsigned long long max);
int desc_ord(const int el1, const int el2);
int asc_ord(const int el1, const int el2);
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               FUNCTION PROTOTYPES                                *
 ************************************************************************************/
