/**************************************
 * pthread-barrier.c
 *
 * Programme d'exemple de barrières
 *
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

void phase1(void)
{
  //
  return;
}


void phase2(void)
{
  //
  return;
}

///AAA
#define NTHREADS 4
pthread_barrier_t rendezvous;

void *compute(void * param) {
  phase1();
  pthread_barrier_wait(&rendezvous);
  phase2();
  return(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t thread[NTHREADS];
  int err;

  err=pthread_barrier_init(&rendezvous, NULL,NTHREADS);
  if(err!=0) {
      error(err,"pthread_barrier_init");
  }
  for(int i=0;i<NTHREADS;i++) {
    err=pthread_create(&(thread[i]),NULL,func[i],NULL);
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
  pthread_barrier_destroy(&srendezvous);
  if(err!=0) {
      error(err,"pthread_barrier_destroy);
  }
  return(EXIT_SUCCESS);
}
///BBB
