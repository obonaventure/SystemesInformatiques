/***********************************************
 * short
 *
 * Overflow sur les shorts
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  ///AAA

  short int i = 1;
  unsigned short j = 1;
  int n;
  
  printf("\nPuissances de 5 en notation signée\n");
  for (n = 1; n < 10; n++) {
    i = i * 5;
    printf("5^%d=%d\n", n, i);
  }
  
  printf("\nPuissances de 10 en notation non signée\n");
  for (n = 1; n < 10; n++) {
    j = j * 10;
    printf("10^%d=%d\n", n, j);
  }

   ///BBB

   return EXIT_SUCCESS;
}
