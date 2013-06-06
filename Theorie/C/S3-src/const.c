/**************************************
 * const.c
 *
 * Programme d'exemple de constantes
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA
// extrait de <math.h>
#define M_PI   3.14159265358979323846264338327950288;

const double pi=3.14159265358979323846264338327950288;

const struct fraction {
  int num;
  int denom;
}  demi={1,2};
///BBB
int main(int argc, char *argv[]) {
  // demi.num=0; invalid
  printf("%d/%d\n",demi.num,demi.denom);
  printf("Adresse de pi :%p\n",&pi);
  printf("Adresse de demi :%p\n",&demi);

  return(EXIT_SUCCESS);
}
