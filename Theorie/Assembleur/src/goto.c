/**************************************
 * goto.c
 *
 * Programme d'exemple pour goto
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define MVAL 2100000000

int m[SIZE][SIZE];

int main(int argc, char *argv[]) {

  srandom(getpid());
  for(int i=0;i<SIZE;i++)
    for(int j=0;j<SIZE;j++) {
      m[i][j]=(int)random();
    }
  ///AAA
  int v=0;
  for(int i=0;i<SIZE;i++)
    for(int j=0;j<SIZE;j++) {
      if(m[i][j]>MVAL) {
	v=m[i][j];
	goto suite;
      }
    }
  printf("aucune valeur supérieure à %d\n",MVAL,v);
  goto fin;
 suite:
  printf("première valeur supérieure à %d : %d\n",MVAL,v);
 fin:
  return(EXIT_SUCCESS);
  ///BBB

}
