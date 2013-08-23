/**************************************
 * callocperf.c
 *
 * Programme mesurant les performances
 * de calloc
 *
 **************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOOP 2

void error(char *msg) {
  fprintf(stderr,"Erreur :%s\n",msg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  int size=1;
  if(argc==2)
    size=atoi(argv[1]);

  for(int j=1;j<LOOP+1;j++) {
    int *vector;
    vector=(int *)calloc(size,sizeof(int));

    int count=0;
    for(int i=0;i<size;i++) {
      if( *(vector+i)!=0)
	count++;
      else
	*(vector+i)=j;
    }
    printf("Nombre d'entiers non initialisés à zéro : %d\n",count);
    free(vector);
  }
  return(EXIT_SUCCESS);
}
