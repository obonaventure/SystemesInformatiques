/**************************************
 * pthread-perf.c
 * 
 * Programme d'exemple pour calculer le coût 
 * de pthread
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100000

void *func(void * param) {
  pthread_exit(NULL);
}


int main (int argc, char *argv[])  {
  int err;
  pthread_t thread;


  for(int i=0;i<N;i++) {

    err=pthread_create(&(thread),NULL,&func,NULL); 
    if(err!=0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
    err=pthread_join(thread,NULL);
    if(err!=0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }
  return(EXIT_SUCCESS);
    
}

