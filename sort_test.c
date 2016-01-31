#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 100

int *insert_sort(int length, int *data);
int *merge_sort(int length, int *data);

int main(void)
{
  int *data_insert[LENGTH];
  int *data_merge[LENGTH];
  time_t time;
  clock_t time_insert;
  clock_t time_merge;

  srand((unsigned) time(&time)); /* seed RNG */

  for (int i = 0; i < LENGTH; ++i) {
    data_insert[i] = rand();
    data_merge[i]  = data_insert[i];
  }


  time_insert = clock();

  insert_sort(LENGTH, data_insert);

  time_insert = clock() - time_insert;


  time_merge = clock();

  merge_sort(LENGTH, data_merge);

  time_merge = clock() - time_merge;

  
  return 0;
}

int *insert_sort(int length, int *data)
{

}

int *merge_sort(int length, int *data)
{

}