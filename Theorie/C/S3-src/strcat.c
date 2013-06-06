/**************************************
 * concat.c
 *
 * Programme d'exemple pour concaténer
 * deux chaînes de caractères
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

int * init_vector(int length, int val) {
  int *ret=malloc(length*sizeof(int));
  for(int i=0;i<length;i++) {
    *(ret+i)=val;
  }
  return(ret);
}

int *unit_matrix(int length) {
  int *r=malloc(length*length*sizeof(int));
  for(int i=0;i<length;i++) {
    for(int j=0;j<length;j++) {
      if(i==j) {
	*(r+(i*length)+j)=1;
      }
      else {
	*(r+(i*length)+j)=0;
      }
    }
  }
  return (r);
}

int main(int argc, char *argv[]) {
  int *v;
  int *m;
  v=init_vector(SIZE,1252);
  m=unit_matrix(SIZE);
  for(int i=0;i<SIZE;i++) {
    printf(" v[%d]=%d",i,*(v+i));
  }
  printf("\n");
  for(int i=0;i<SIZE;i++) {
    for(int j=0;j<SIZE;j++) {
      printf(" m[%d,%d]=%d",i,j,*(m+(i*SIZE)+j));
    }
    printf("\n");
  }
  printf("\n");
  free(v);
  free(m);
  return(EXIT_SUCCESS);
}
