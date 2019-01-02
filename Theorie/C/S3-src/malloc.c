/**************************************
 * malloc.c
 *
 * Programme illustrant malloc
 *
 **************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct fraction {
  int num;
  int den;
} Fraction;

void error(char *msg) {
  fprintf(stderr,"Erreur :%s\n",msg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  int size=1;
  if(argc==2)
    size=atoi(argv[1]);

  char * string;
  printf("Valeur du pointeur string avant malloc : %p\n",string);
  string=(char *) malloc((size+1)*sizeof(char));
  if(string==NULL)
    error("malloc(string)");

  printf("Valeur du pointeur string après malloc : %p\n",string);
  int *vector;
  vector=(int *)malloc(size*sizeof(int));
  if(vector==NULL)
    error("malloc(vector)");

  Fraction * fract_vect;
  fract_vect=(Fraction *) malloc(size*sizeof(Fraction));
  if(fract_vect==NULL)
    error("malloc(fract_vect)");

  free(string);
  printf("Valeur du pointeur string après free   : %p\n",string);
  string=NULL;
  free(vector);
  vector=NULL;
  free(fract_vect);
  fract_vect=NULL;

  return(EXIT_SUCCESS);
}
///BBB
