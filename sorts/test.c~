#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *strcpy_string  = (char *) malloc(25);
  char *stpncpy_string = (char *) malloc(25);
  int i;

  for (i = 0; i < 25; i += 3) {

    /* strcpy(strcpy_string[i], {'a', 'b', 'c'}); */
    stpncpy_string = stpncpy(stpncpy_string, "abc", 3);
    
  }

  stpncpy_string[i] = '\0';

  puts(stpncpy_string);
  
  return 0;
}
