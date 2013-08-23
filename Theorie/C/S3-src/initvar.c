/**************************************
 * initvar.c
 *
 * Programme d'exemple sur l'initialisation
 * des variables
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA

#define ARRAY_SIZE 1000

// initialise un tableau local
void init(void) {
  long a[ARRAY_SIZE];
  for(int i=0;i<ARRAY_SIZE;i++) {
    a[i]=i;
  }
}

// retourne la somme des éléments
// d'un tableau local
long read(void) {
  long b[ARRAY_SIZE];
  long sum=0;
  for(int i=0;i<ARRAY_SIZE;i++) {
    sum+=b[i];
  }
  return sum;
}


///BBB
int main(int argc, char *argv[]) {
  unsigned int n=5;

  if(argc==2) {
    n=atoi(argv[1]);
  }

  ///CCC
  printf("Résultat de read() avant init(): %ld\n",read());
  init();
  printf("Résultat de read() après init() : %ld\n",read());
  ///DDD
  return(EXIT_SUCCESS);
}
