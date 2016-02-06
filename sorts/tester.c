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


void report(struct SortAlg *algs, const size_t num_algs)
{
  size_t num_cols;
  size_t pad_gutter;
  size_t line_width;
  size_t alg_index;
  size_t buf_index;
  size_t col_width;
  size_t col_index;
  size_t cont_byte_offset;
  size_t buffer_size;
  struct winsize window;
  int cont_width;
  char *buffer;
  char **lines;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  num_cols   = num_algs + 1;
  pad_gutter = (num_cols * 3) + 1;
  col_width  = (window.ws_col - pad_gutter) / num_cols;
  cont_width = col_width - 1;
  cont_byte_offset = col_width + 3;
  line_width = (col_width * num_cols) + pad_gutter;

  buffer_size = line_width + (2 * (num_cols + 1)) + 1;

  buffer = (char *) malloc(sizeof(char) * buffer_size);

  sprintf(buffer, "┃ %-*s┃", cont_width, "ALGORITHM");

  lines = build_lines(line_width, col_width, num_cols);

  puts(lines[0]); /* print top border line */

  buf_index = cont_byte_offset + 3;

  for (alg_index = 0; alg_index < num_algs; ++alg_index) {

    sprintf(&buffer[buf_index], " %-*s│", cont_width, algs[alg_index].alg_name);

    buf_index += cont_byte_offset;
  }
  puts(buffer);
  puts(lines[1]); /* print bottom border line */
  puts(lines[2]); /* print bottom border line */
}
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*
 *                               TOP LEVEL FUNCTIONS                                *
 ************************************************************************************/
/************************************************************************************
 *                                 HELPER FUNCTIONS                                 *
 *▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼*/
char **build_lines(const size_t line_width, const size_t col_width, const size_t num_cols)
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
	lines[1][2] = '\xA0'; /* set left edge of mid line to "┠" */
	lines[2][2] = '\x97'; /* set left edge of bot line to "┗" */


  /* set first cols of horiz lines */
  byte_index = 3;
  byte_cutoff = col_bytes + 3;

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

	/* for (line_index = 0; line_index < 3; ++line_index) { */
    /* byte_index = 3; */
    /* while (byte_index < byte_cutoff) { */
      /* /1* all lines share first col of heavy box char "━" *1/ */
      /* lines[line_index][byte_index] = '\xE2'; */
      /* ++byte_index; */
      /* lines[line_index][byte_index] = '\x94'; */
      /* ++byte_index; */
      /* lines[line_index][byte_index] = '\x81'; */
      /* ++byte_index; */
    /* } */
	/* } */


/*   /1* set first joiners *1/ */
/* 	lines[0][byte_index] = '\xE2'; */
/* 	lines[1][byte_index] = '\xE2'; */
/* 	lines[2][byte_index] = '\xE2'; */
/*   ++byte_index; */
/* 	lines[0][byte_index] = '\x94'; */
/* 	lines[1][byte_index] = '\x95'; */
/* 	lines[2][byte_index] = '\x94'; */
/*   ++byte_index; */
/* 	lines[0][byte_index] = '\xB3'; /1* set left edge of top line to "┳" *1/ */
/* 	lines[1][byte_index] = '\x89'; /1* set left edge of mid line to "╉" *1/ */
/* 	lines[2][byte_index] = '\xBB'; /1* set left edge of bot line to "┻" *1/ */
/*   ++byte_index; */


  /* build body of lines with cols and joiners */
  /* col_cutoff = num_cols - 1; */

	for (col_index = 1; col_index < num_cols; ++col_index) {
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
  }


/*   /1* set final col of box char lines *1/ */
/*   byte_cutoff = byte_index + col_bytes; */

/*   while (byte_index < byte_cutoff) { */
/*     lines[0][byte_index] = '\xE2'; */
/*     lines[1][byte_index] = '\xE2'; */
/*     lines[2][byte_index] = '\xE2'; */
/*     ++byte_index; */
/*     lines[0][byte_index] = '\x94'; */
/*     lines[1][byte_index] = '\x94'; */
/*     lines[2][byte_index] = '\x94'; */
/*     ++byte_index; */
/*     lines[0][byte_index] = '\x81'; /1* top line has col of heavy box char '━' *1/ */
/*     lines[1][byte_index] = '\x80'; /1* mid line has col of light box char '─' *1/ */
/*     lines[2][byte_index] = '\x81'; /1* bot line has col of heavy box char '━' *1/ */
/*     ++byte_index; */
/*   } */


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
