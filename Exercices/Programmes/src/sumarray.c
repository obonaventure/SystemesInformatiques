/**************************************
 * sumarray.c
 *
 * Programme d'exemple pour calculer la
 * somme des éléments d'une matrice
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

/* Return t2-t1 in microseconds */
long timeval_diff(struct timeval *t2, struct timeval *t1)
{
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
  return (diff);
}

///AAA
#define SIZE 10000

int matrix[SIZE][SIZE];

int sum() {
  int sum=0;
  for(int i=0;i<SIZE;i++) {
    for(int j=0;j<SIZE;j++) {
      sum+=matrix[i][j];
    }
  }
  return sum;
}

int sum2() {
  int sum=0;
  for(int i=0;i<SIZE;i++) {
    for(int j=0;j<SIZE;j++) {
      sum+=matrix[j][i];
    }
  }
  return sum;
}
///BBB

int main(int argc, char *argv[]) {

  for(int i=0;i<SIZE;i++) {
    for(int j=0;j<SIZE;j++) {
      matrix[i][j]=1;
    }
  }
  printf("%d \n",sum());
  printf("%d \n",sum2());

   return(EXIT_SUCCESS);
}
