/**************************************
 * pthread-neg.c
 *
 * Programme d'exemple de pthread utilisant les
 * arguments et retournant une valeur
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
#define SIZE 100

pthread_t mythread;

void *f(void *param) {
  int *v=(int *) param;
  long r=0;
  for(long i=0;i<SIZE;i++) {
    r+=v[i];
  }
  return((void *) r);
}

void launch(void ){
  int v[SIZE];
  for(int i=0;i<SIZE;i++) {
    v[i]=1;
  }
  int err=pthread_create(&(mythread),NULL,&f,(void *) v);
  if(err!=0)
    error(err,"pthread_create");
}


int main (int argc, char *argv[])  {

  launch();
  // ...
  return(EXIT_SUCCESS);
}
