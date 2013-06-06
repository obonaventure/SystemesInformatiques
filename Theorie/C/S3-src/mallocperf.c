/**************************************
 * mallocperf.c
 *
 * Programme mesurant les performances
 * de malloc
 *
 **************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


#define LOOP 10
#define SIZE 1000000000

void error(char *msg) {
  fprintf(stderr,"Erreur :%s\n",msg);
  exit(EXIT_FAILURE);
}

/* Return t2-t1 in microseconds */
long timeval_diff(struct timeval *t2, struct timeval *t1)
{
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
  return (diff);
}

int main(int argc, char *argv[]) {

  int *vector;
  long mesures[LOOP], sum;

  struct timeval tvStart, tvEnd;
  int err;

  vector=(int *)malloc(SIZE*sizeof(int));
  free(vector);

  for(int i=0;i<LOOP+1;i++) {
    err=gettimeofday(&tvStart, NULL);
    if(err!=0)
      exit(EXIT_FAILURE);

     vector=(int *)calloc(SIZE,sizeof(int));
     //vector=(int *)malloc(SIZE*sizeof(int));
    err=gettimeofday(&tvEnd, NULL);
    if(err!=0)
      exit(EXIT_FAILURE);

    mesures[i]=timeval_diff(&tvEnd, &tvStart);
    sum+=mesures[i];
    free(vector);
  }
  printf("Durée moyenne : %ld\n",sum/LOOP);

  return(EXIT_SUCCESS);
}
