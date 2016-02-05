/************************************************************************************
 *                                     tester.c                                     *
 *                                                                                  *
 * Module for testing basic merge and insertion sorts.                              *
 ************************************************************************************/
/************************************************************************************
 *                             PREPROCESSOR DIRECTIVES                              *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
#include "tester.h"
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                             PREPROCESSOR DIRECTIVES                              *
 ************************************************************************************/
/************************************************************************************
 *                               TOP LEVEL FUNCTIONS                                *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
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

  num_cols   = num_algs + 1;
  pad_gutter = (num_cols * 3) + 1;
  col_width  = (window.ws_col - pad_gutter) / num_cols;
  line_width = (col_width * num_cols) + pad_gutter;

  lines = build_lines(line_width, col_width, num_cols);
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               TOP LEVEL FUNCTIONS                                *
 ************************************************************************************/
/************************************************************************************
 *                                 HELPER FUNCTIONS                                 *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
char **build_lines(const int line_width, const int col_width, const int num_cols)
{
  int line_index;
  int col_index;
  int byte_index;
  int col_cutoff;
  int byte_cutoff;
  size_t row_bytes;
  size_t col_bytes;
  size_t line_bytes;
	char **lines;

  row_bytes  = sizeof(char *) * 3;
  /* bytes to a column of box char lines */
  col_bytes  = sizeof(char) * col_width * 3;
  line_bytes = (sizeof(char) * line_width * 3) + 1;

  /* allocate memory for 3 line pointers */
  lines = (char **) malloc(row_bytes);
  if (lines == NULL) {
    fprintf(stderr, "failed of allocate %lu bytes for line rows\n",
        row_bytes);
    exit(1);
  }

/* ┏┳┓┣╋┫┗┻┛ ━ ┃ */
	for (line_index = 0; line_index < 3; ++line_index) {
    /* allocate memory for each line */
    lines[line_index] = (char *) malloc(line_bytes);
    if (lines[line_index] == NULL) {
      fprintf(stderr, "failed of allocate %lu bytes for line: %i\n",
          line_bytes, line_index);
      exit(1);
    }
    /* all lines' first box chars share first 2 bytes */
		lines[line_index][0] = '\xE2';
		lines[line_index][1] = '\x94';
	}
	lines[0][2] = '\x8F'; /* set left edge of top line to "┏" */
	lines[1][2] = '\xA3'; /* set left edge of mid line to "┣" */
	lines[2][2] = '\x97'; /* set left edge of bot line to "┗" */


  /* set first cols of horiz lines */
  byte_cutoff = col_bytes + 3;

	for (line_index = 0; line_index < 3; ++line_index) {
    byte_index = 3;
    while (byte_index < byte_cutoff) {
      /* all lines share first col of heavy box char "━" */
      lines[line_index][byte_index] = '\xE2';
      ++byte_index;
      lines[line_index][byte_index] = '\x94';
      ++byte_index;
      lines[line_index][byte_index] = '\x81';
      ++byte_index;
    }
	}


  /* set first joiners */
	lines[0][byte_index] = '\xE2';
	lines[1][byte_index] = '\xE2';
	lines[2][byte_index] = '\xE2';
  ++byte_index;
	lines[0][byte_index] = '\x94';
	lines[1][byte_index] = '\x95';
	lines[2][byte_index] = '\x94';
  ++byte_index;
	lines[0][byte_index] = '\xB3'; /* set left edge of top line to "┳" */
	lines[1][byte_index] = '\x89'; /* set left edge of mid line to "╉" */
	lines[2][byte_index] = '\xBB'; /* set left edge of bot line to "┻" */
  ++byte_index;


  /* build body of lines with cols and joiners */
  col_cutoff = num_cols - 1;

	for (col_index = 1; col_index < col_cutoff; ++col_index) {
    byte_cutoff = byte_index + col_bytes;

    while (byte_index < byte_cutoff) {
      lines[0][byte_index] = '\xE2';
      lines[1][byte_index] = '\xE2';
      lines[2][byte_index] = '\xE2';
      ++byte_index;
      lines[0][byte_index] = '\x94';
      lines[1][byte_index] = '\x94';
      lines[2][byte_index] = '\x94';
      ++byte_index;
      lines[0][byte_index] = '\x81'; /* top line has col of heavy box char '━' */
      lines[1][byte_index] = '\x80'; /* mid line has col of light box char '─' */
      lines[2][byte_index] = '\x81'; /* bot line has col of heavy box char '━' */
      ++byte_index;
    }

    lines[0][byte_index] = '\xE2';
    lines[1][byte_index] = '\xE2';
    lines[2][byte_index] = '\xE2';
    ++byte_index;
    lines[0][byte_index] = '\x94';
    lines[1][byte_index] = '\x94';
    lines[2][byte_index] = '\x94';
    ++byte_index;
    lines[0][byte_index] = '\xAF'; /* set right edge of top line to "┯" */
    lines[1][byte_index] = '\xBC'; /* set right edge of mid line to "┼" */
    lines[2][byte_index] = '\xB7'; /* set right edge of bot line to "┷" */
    ++byte_index;
  }


  /* set final col of box char lines */
  byte_cutoff = byte_index + col_bytes;

  while (byte_index < byte_cutoff) {
    lines[0][byte_index] = '\xE2';
    lines[1][byte_index] = '\xE2';
    lines[2][byte_index] = '\xE2';
    ++byte_index;
    lines[0][byte_index] = '\x94';
    lines[1][byte_index] = '\x94';
    lines[2][byte_index] = '\x94';
    ++byte_index;
    lines[0][byte_index] = '\x81'; /* top line has col of heavy box char '━' */
    lines[1][byte_index] = '\x80'; /* mid line has col of light box char '─' */
    lines[2][byte_index] = '\x81'; /* bot line has col of heavy box char '━' */
    ++byte_index;
  }


  /* set final joiners */
	lines[0][byte_index] = '\xE2';
	lines[1][byte_index] = '\xE2';
	lines[2][byte_index] = '\xE2';
  ++byte_index;
	lines[0][byte_index] = '\x94';
	lines[1][byte_index] = '\x94';
	lines[2][byte_index] = '\x94';
  ++byte_index;
	lines[0][byte_index] = '\x93'; /* set right edge of top line to "┓" */
	lines[1][byte_index] = '\xA8'; /* set right edge of mid line to "┨" */
	lines[2][byte_index] = '\x9B'; /* set right edge of bot line to "┛" */
  ++byte_index;

  /* terminate lines with null byte */
	lines[0][byte_index] = '\x00';
	lines[1][byte_index] = '\x00';
	lines[2][byte_index] = '\x00';

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
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                                 HELPER FUNCTIONS                                 *
 ************************************************************************************/


