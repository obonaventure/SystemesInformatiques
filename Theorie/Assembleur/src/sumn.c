/**************************************
 * sumn.c
 *
 * Programme d'exemple pour un calcul récursif
 * de la somme des n premiers entiers
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>


int g=0;
int h=0;
///CCC
int sumn_iter(int n) {
  int sum=0;
  for(int i=1;i<=n;i++)
    sum+=i;
  return sum;
}
///AAA
int sumn(int n) {
  if(n<=1)
    return n;
  else
    return n+sumn(n-1);
}
///BBB
int main(int argc, char *argv[]) {
  g=sumn(3);
  h=sumn_iter(3);
  return(EXIT_SUCCESS);
}
