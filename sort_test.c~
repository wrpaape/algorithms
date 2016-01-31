#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 100

int *insert_sort(int length, int *data);
int *merge_sort(int length, int *data);

int main(void)
{
  int data_insert[LENGTH];
  int data_merge[LENGTH];
  clock_t time_insert;
  clock_t time_merge;

  srand(time(NULL)); /* seed RNG */

  for (int i = 0; i < LENGTH; ++i) {
    data_insert[i] = rand();
    data_merge[i]  = data_insert[i];
  }


  /* time insertion sort */
  puts("timing insert_sort...");
  time_insert = clock();
  insert_sort(LENGTH, data_insert);
  time_insert = clock() - time_insert;
  puts("done\n");


  /* time merge sort */
  puts("timing merge_sort...");
  time_merge = clock();
  merge_sort(LENGTH, data_merge);
  time_merge = clock() - time_merge;
  puts("done\n");

  printf("\nN = %i\ninsert: %lu μs\nmerge:  %lu μs\n",
      LENGTH, time_insert, time_merge);

  puts("unsorted | sorted:\n");
  for (int i = 0; i < LENGTH; ++i) {
   printf("%i | %i\n", data_merge[i], data_insert[i]); 
  }
  
  return 0;
}

int *insert_sort(int length, int *data)
{
  int temp;
  int j;

  for (int i = 1; i < length; ++i) {
    temp = data[i];
    j = i - 1;
    
    while ((j > -1) && (data[j] > temp)) {
      data[j + 1] = data[j];
      --j;
    }

    data[j + 1] = temp;
  }

  return data;

}

int *merge_sort(int length, int *data)
{

  return data;
}
