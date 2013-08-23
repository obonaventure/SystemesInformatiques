/**************************************
 * sigfpe.c
 *
 * Programme d'exemple de signal sigfpe
 * fichiers
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])  {
  int n=1252;
  int zero=0;
  printf("Calcul de : %d/%d\n",n,zero);
  fflush(stdout);
  printf("Résultat : %d\n",n/zero);

  return(EXIT_SUCCESS);
}
///BBB
