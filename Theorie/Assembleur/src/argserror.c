/**************************************
 * argserror.c
 *
 * Programme d'exemple d'appel de fonction
 * avec un nombre erroné d'arguments
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

int g;

int f(int i, int j) {
  return i+j;
}

int main(int argc, char *argv[]) {

  g=f(3,0);
  // g=f(5,6,7);

  return(EXIT_SUCCESS);
}
