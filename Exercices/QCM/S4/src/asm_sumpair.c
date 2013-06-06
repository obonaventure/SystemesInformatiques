/**************************************
 * sumn.c
 *
 * Programme d'exemple pour un calcul récursif
 * de la somme des n premiers nombres impairs
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>


///AAA
int ndiv(int n) {
  if(n%2==0)
    return sumn(n-1);
  else
    return n+sumn(n-1);
}
///BBB
int main(int argc, char *argv[]) {
  g=sumn(3);
  h=sumn_iter(3);
  return(EXIT_SUCCESS);
}
