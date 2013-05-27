/**************************************
 * ptrptr.c
 *
 * Programme d'exemple pour les pointeurs
 * vers des pointeurs
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
///AAA
int main(int argc, char **argv) {

  char **p;
  p=argv;
  printf("Arguments :");
  while(*p!=NULL) {
    printf(" %s",*p);
    p++;
  }
  printf("\n");
  return(EXIT_SUCCESS);
}
///BBB
