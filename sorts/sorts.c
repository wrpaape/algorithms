/************************************************************************************
 *                                     sorts.c                                      *
 *                                                                                  *
 * Module for prototyping and testing basic merge and insertion sorts.              *
 ************************************************************************************/
/************************************************************************************
 *                             PREPROCESSOR DIRECTIVES                              *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include <sys/ioctl.h>


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
int *insert_sort_by(int *data, const size_t length,
    int (*sort_by)(const int el1, const int el2));
int *merge_sort_by( int *data, const size_t length,
    int (*sort_by)(const int el1, const int el2));
int *select_sort_by(int *data, const size_t length,
    int (*sort_by)(const int el1, const int el2));

void test_algs(struct SortAlg *alg_ptr, const size_t length);
void report(struct SortAlg *alg_ptr, const int num_algs);

/* helper */
char **build_lines(const int line_width, const int col_width, const int num_cols);
int *shuffle(int *data, const unsigned long long length);
unsigned long long rand_upto(const unsigned long long max);
int desc_ord(const int el1, const int el2);
int asc_ord(const int el1, const int el2);
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               FUNCTION PROTOTYPES                                *
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

void test_algs(struct SortAlg *alg_ptr, const size_t length)
{
  struct TestOrd *ord_ptr;
  struct TestDir *dir_ptr;
  int alg_index; /* index of current sorting algorthim */
  int ord_index; /* index of current data ordering */
  int dir_index; /* index of current sort direction */

  /* for each sorting algorithm */
  for (alg_index = 0; alg_index < length; ++alg_index, ++alg_ptr) {

    printf("\e[2Jsorting algorithm: %s\e[5m...\e[25m\n", alg_ptr -> alg_name);

    ord_ptr = &(alg_ptr -> test_ords[0]);

    /* for each ordering of data */
    for (ord_index = 0; ord_index < ORDS_PER_ALG; ++ord_index, ++ord_ptr) {

      printf("  data order: %s\e[5m...\e[25m\n", ord_ptr -> init_ord);

      dir_ptr = &(ord_ptr -> test_dirs[0]);

      /* for each sort direction */
      for (dir_index = 0; dir_index < DIRS_PER_ORD; ++dir_index, ++dir_ptr) {
        printf("    sorting direction: %s\e[5m...\e[25m", dir_ptr -> sort_dir);

        dir_ptr -> sort_time = clock();

        (alg_ptr -> alg_func)(dir_ptr -> data, LENGTH, dir_ptr -> sort_by);

        dir_ptr -> sort_time -= clock();

        puts("done");
      }
      
      puts("  done");
    }

    puts("done\n");
  }
}

void report(struct SortAlg *alg_ptr, const int num_algs)
{
  struct winsize window;
  int num_cols;
  size_t pad_gutter;
  int col_width;
  int col_index;
  size_t line_width;
  size_t line_bytes;
  size_t alg_index;
  char **lines;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
  /* ioctl(fileno(stdout), TIOCGWINSZ, &window); */

  num_cols   = num_algs + 1;
  pad_gutter = (num_cols * 3) + 1;
  col_width  = (window.ws_col - pad_gutter) / num_cols;
  line_width = (col_width * num_cols) + pad_gutter;

  lines = build_lines(line_width, col_width, num_cols);


  /* clear window => inverse ANSI => print top border */
  /* printf("\e[2J\e[7m%s\n║ %-*s ", lines, col_width, "sorting algorithm"); */

  /* for (alg_index = 0; alg_index < length; ++alg_index) { */
  /*   printf("┃ %-*s ", col_width, alg_ptr[alg_index].alg_name); */
  /* } */
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               TOP LEVEL FUNCTIONS                                *
 ************************************************************************************/
/************************************************************************************
 *                                 HELPER FUNCTIONS                                 *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/

/* ╔╦╗╠╬╣╣╚╩╝║═ */
/* [{"╔", <<226, 149, 148, 0>>}, {"╦", <<226, 149, 166, 0>>}, */
/*  {"╗", <<226, 149, 151, 0>>}, {"╠", <<226, 149, 160, 0>>}, */
/*  {"╬", <<226, 149, 172, 0>>}, {"╣", <<226, 149, 163, 0>>}, */
/*  {"╣", <<226, 149, 163, 0>>}, {"╚", <<226, 149, 154, 0>>}, */
/*  {"╩", <<226, 149, 169, 0>>}, {"╝", <<226, 149, 157, 0>>}, */
/*  {"║", <<226, 149, 145, 0>>}, {"═", <<226, 149, 144, 0>>}] */

/* ┏┳┓┣╋┫┗┻┛ ━ ┃ */
/* [{"┏", <<226, 148, 143, 0>>}, {"┳", <<226, 148, 179, 0>>}, */
/*  {"┓", <<226, 148, 147, 0>>}, {"┣", <<226, 148, 163, 0>>}, */
/*  {"╋", <<226, 149, 139, 0>>}, {"┫", <<226, 148, 171, 0>>}, */
/*  {"┗", <<226, 148, 151, 0>>}, {"┻", <<226, 148, 187, 0>>}, */
/*  {"┛", <<226, 148, 155, 0>>}, {"━", <<226, 148, 129, 0>>}, */
/*  {"┃", <<226, 148, 131, 0>>}] */

/* [{"╉", <<226, 149, 137, 0>>}, {"┨", <<226, 148, 168, 0>>}] */
char **build_lines(const int line_width, const int col_width, const int num_cols)
{
  int line_index;
  int col_index;
  int byte_index;
  size_t row_bytes;
  size_t col_bytes;
  size_t line_bytes;
	char **lines;
  int col_byte_cutoff;

  row_bytes  = (sizeof(char *) * 3);
  col_bytes  = (sizeof(char) * col_width * 3);
  line_bytes = (sizeof(char) * line_width * 3) + 1;
  lines      = (char **) malloc(row_bytes);

  if (lines == NULL) {
    fprintf(stderr, "failed of allocate %lu bytes for line rows\n",
        row_bytes);
    exit(1);
  }

	for (line_index = 0; line_index < 3; ++line_index) {
    lines[line_index] = (char *) malloc(line_bytes);

    if (lines[line_index] == NULL) {
      fprintf(stderr, "failed of allocate %lu bytes for line: %i\n",
          line_bytes, line_index);
      exit(1);
    }

		lines[line_index][0] = '\xE2';
		lines[line_index][1] = '\x95';
	}


	lines[0][2]     = '\x94';
	lines[1][2]     = '\xA0';
	lines[2][2]     = '\x9A';
  col_byte_cutoff = col_bytes + 3;

	for (line_index = 0; line_index < 3; ++line_index) {
    byte_index = 3;
    while (byte_index < col_byte_cutoff) {
      lines[line_index][byte_index] = '\xE2';
      ++byte_index;
      lines[line_index][byte_index] = '\x95';
      ++byte_index;
      lines[line_index][byte_index] = '\x90';
      ++byte_index;
    }
	}


	lines[0][col_byte_cutoff + 1] = '\x00';
	lines[1][col_byte_cutoff + 1] = '\x00';
	lines[2][col_byte_cutoff + 1] = '\x00';

  /* for (byte_index = 0; byte_index < col_bytes; byte_index += 3) { */

  /* } */

  puts(lines[0]);
  puts(lines[1]);
  puts(lines[2]);

  return lines;
}


int *shuffle(int *data, const unsigned long long length)
{
  int temp;
  unsigned long long rand_index;
  unsigned long long main_index;

  srandom(time(NULL)); /* seed RNG */

  main_index = length - 1;

  while (main_index > 0) {
    rand_index       = rand_upto(main_index);
    temp             = data[main_index];
    data[main_index] = data[rand_index];
    data[rand_index] = temp;

    --main_index;
  }

  return data;
}


unsigned long long rand_upto(const unsigned long long max)
{
  const unsigned long long range_max  = (unsigned long long) max + 1;
  const unsigned long long range_rand = (unsigned long long) RAND_MAX + 1;
  const unsigned long long bin_size   = range_rand / range_max;
  const unsigned long long overflow   = range_rand % range_max;
  const unsigned long long max_valid  = RAND_MAX - overflow;

  unsigned long long rand_val;

  do {

    rand_val = random();

  } while (rand_val > max_valid);

  return (rand_val / bin_size);
}


int desc_ord(const int el1, const int el2)
{
  return (el1 > el2);
}


int asc_ord(const int el1, const int el2)
{
  return (el1 < el2);
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                                 HELPER FUNCTIONS                                 *
 ************************************************************************************/
