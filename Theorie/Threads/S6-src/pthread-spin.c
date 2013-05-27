/**************************************
 * pthread-spin.c
 *
 * Programme d'exemple de pthread avec
 * utilisation de spinlock pour éviter une
 * violation de section critique
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

///AAA

#define NTHREADS 4

long global=0;

static pthread_spinlock_t spinlock_global;


int increment(int i) {
  return i+1;
}

void *func(void * param) {
  for(int j=0;j<1000000;j++) {
    pthread_spin_lock(&spinlock_global);
    global=increment(global);
    pthread_spin_unlock(&spinlock_global);
  }
  return(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t thread[NTHREADS];
  int err;

  pthread_spin_init( &spinlock_global, 0);

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_create(&(thread[i]),NULL,&func,NULL);
    if(err!=0)
      error(err,"pthread_create");
  }
  for(int i=0; i<1000000000;i++) { /*...*/ }

  for(int i=NTHREADS-1;i>=0;i--) {
    err=pthread_join(thread[i],NULL);
    if(err!=0)
      error(err,"pthread_join");
  }

  printf("global: %ld\n",global);

  return(EXIT_SUCCESS);
}
