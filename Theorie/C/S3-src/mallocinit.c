/**************************************
 * mallocinit.c
 *
 * Malloc et les données non-initialisées
 *
 **************************************/
#include <stdio.h>
#include <stdlib.h>
///AAA
#define LEN 1024

int main(int argc, char *argv[]) {

  int *v1;
  int *v2;
  int sum=0;
  v1=(int *)malloc(sizeof(int)*LEN);
  for(int i=0;i<LEN;i++) {
    sum+=*(v1+i);
    *(v1+i)=1252;
  }
  printf("Somme des éléments de v1 : %d\n", sum);
  sum=0;
  free(v1);
  v2=(int *)malloc(sizeof(int)*LEN);
  for(int i=0;i<LEN;i++) {
    sum+=*(v2+i);
  }

  printf("Somme des éléments de v2 : %d\n", sum);
  free(v2);

  return(EXIT_SUCCESS);
}
