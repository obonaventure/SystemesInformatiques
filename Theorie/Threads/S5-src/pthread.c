/**************************************
 * pthread.c
 *
 * Programme d'exemple de pthread
 *
 **************************************/
///AAA
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
  pthread_t first;
  pthread_t second;
  int err;

  err=pthread_create(&first,NULL,&thread_first,NULL);
  if(err!=0)
    error(err,"pthread_create");

  err=pthread_create(&second,NULL,&thread_second,NULL);
  if(err!=0)
    error(err,"pthread_create");

  for(int i=0; i<1000000000;i++) { /*...*/ }

  err=pthread_join(second,NULL);
    if(err!=0)
      error(err,"pthread_join");

  err=pthread_join(first,NULL);
    if(err!=0)
      error(err,"pthread_join");

  printf("global: %d\n",global);

  return(EXIT_SUCCESS);
}
