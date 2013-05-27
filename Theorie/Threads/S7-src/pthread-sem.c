/**************************************
 * pthread-semt.c
 *
 * Programme d'exemple de sémaphores
 *
 **************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NTHREADS 4

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}


///AAA

static sem_t semaphore;
long global=0;

int increment(int i) {
  return i+1;
}

void *inc(void * param) {
  for(int j=0;j<1000000;j++) {
    sem_wait(&semaphore);
    global=increment(global);
    sem_post(&semaphore);
  }
  pthread_exit(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t thread[NTHREADS];
  int err;

  sem_init(&semaphore, 0,1);

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_create(&(thread[i]),NULL,&inc,NULL);
    if(err!=0) {
      error(err,"pthread_create");
    }
  }

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_join(thread[i],NULL);
    if(err!=0) {
      error(err,"pthread_join");
    }
  }
  sem_destroy(&semaphore);
  printf("global: %ld\n",global);

  return(EXIT_SUCCESS);
}
