/***********************************************
 * arrayvar.c
 *
 * Programme d'exemple d'utilisation de tableaux
 * de taille non prédéfinie à la compilation
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

void init(int size, int v[]) {
  int i;
  for(i=0;i<size;i++)
    v[i]=1;

}


int main(int argc, char *argv[]) {
  /*
  int size;
  int vecteur[];
  int i;
  if(argc!=1) {
    fprintf(stderr, "Usage : arrayvar n avec n entier\n");
    return(EXIT_FAILURE);
  }
  size=atoi(argv[1]);
  */

  ///CCC
  int vecteur[N]={0,1,2,3,4,5,6,7,8,9};
  int i;
  int sum=0;
  for(i=0;i<N; i++) {
    sum+=vecteur[i];
  }
  ///DDD


  return(EXIT_SUCCESS);
}
