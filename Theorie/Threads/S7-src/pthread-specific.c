/**************************************
 * pthread-specific.c
 *
 * Programme d'exemple de pthread qui utilise une
 * zone mémoire pour stocker des données
 * spécifiques au thread
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}


///AAA
#define LOOP 1000000
#define NTHREADS 4

__thread int count=0;
int global_count=0;

void *f( void* param) {
  for(int i=0;i<LOOP;i++) {
    count++;
    global_count=global_count-1;
  }
  printf("Valeurs : count=%d, global_count=%d\n",count, global_count);
  return(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t threads[NTHREADS];
  int err;

  for(int i=0;i<NTHREADS;i++) {
    count=i;   // local au thread du programme principal
    err=pthread_create(&(threads[i]),NULL,&f,NULL);
    if(err!=0)
      error(err,"pthread_create");
  }

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_join(threads[i],NULL);
    if(err!=0)
      error(err,"pthread_create");
  }

  return(EXIT_SUCCESS);
}
///BBB
