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

pthread_key_t count;
int global_count=0;

void g(void ) {
  void * data=pthread_getspecific(count);
  if(data==NULL)
    error(-1,"pthread_getspecific");
  int *count_ptr=(int *)data;
  for(int i=0;i<LOOP;i++) {
    *count_ptr=*(count_ptr)+1;
    global_count=global_count-1;
  }
}

void *f( void* param) {
  int err;
  int *int_ptr=malloc(sizeof(int));
  *int_ptr=0;
  err=pthread_setspecific(count, (void *)int_ptr);
  if(err!=0)
    error(err,"pthread_setspecific");
  g();
  printf("Valeurs : count=%d, global_count=%d\n",*int_ptr, global_count);
  free(int_ptr);
  return(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t threads[NTHREADS];
  int err;

  err=pthread_key_create(&(count),NULL);
  if(err!=0)
    error(err,"pthread_key_create");

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_create(&(threads[i]),NULL,&f,NULL);
    if(err!=0)
      error(err,"pthread_create");
  }

  for(int i=0;i<NTHREADS;i++) {
    err=pthread_join(threads[i],NULL);
    if(err!=0)
      error(err,"pthread_create");
  }
  err=pthread_key_delete(count);
  if(err!=0)
    error(err,"pthread_key_delete");

  return(EXIT_SUCCESS);
}
///BBB
