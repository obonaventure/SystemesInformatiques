/**************************************
 * pthread.c
 *
 * Programme d'exemple de pthread
 *
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int global=0;

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}

void *thread_first(void * param) {
  global++;
  return(NULL);
}

void *thread_second(void * param) {
  global++;
  pthread_exit(NULL);
}

int main (int argc, char *argv[])  {

  ///AAA
  pthread_t first;
  pthread_attr_t attr_first;
  size_t stacksize;

  int err;

  err= pthread_attr_init(&attr_first);
  if(err!=0)
    error(err,"pthread_attr_init");

  err= pthread_attr_getstacksize(&attr_first,&stacksize);
  if(err!=0)
    error(err,"pthread_attr_getstacksize");

  printf("Taille par défaut du stack : %ld\n",stacksize);

  stacksize=65536;

  err= pthread_attr_setstacksize(&attr_first,stacksize);
  if(err!=0)
    error(err,"pthread_attr_setstacksize");

  err=pthread_create(&first,&attr_first,&thread_first,NULL);
  if(err!=0)
    error(err,"pthread_create");
  ///BBB

  for(int i=0; i<1000000000;i++) { /*...*/ }


  err=pthread_join(first,NULL);
    if(err!=0)
      error(err,"pthread_join");

  printf("global: %d\n",global);

  return(EXIT_SUCCESS);
}
