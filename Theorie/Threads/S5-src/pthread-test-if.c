/**************************************
 * pthread-test.c
 *
 * Programme d'exemple de pthread avec condition de course
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

long global=0;
int even=0;
int odd=0;

void test_even(int i) {
  if((i%2)==0)
    even++;
}

int increment(int i) {
  return i+1;
}

void *inc(void * param) {
  for(int j=0;j<1000000;j++) {
    global=increment(global);
  }
  pthread_exit(NULL);
}

void *even(void * param) {
  for(int j=0;j<1000000;j++) {
    test_even(global);
  }
  pthread_exit(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t thread_inc;
  pthread_t thread_even;
  int err;

  err=pthread_create(&(thread_inc),NULL,&inc,NULL);
  if(err!=0) {
    error(err,"pthread_create");
  }

  err=pthread_create(&(thread_even),NULL,&inc,NULL);
  if(err!=0) {
    error(err,"pthread_create");
  }

  err=pthread_join(thread_inc,NULL);
  if(err!=0)
    error(err,"pthread_join");
  }

  err=pthread_join(thread_even,NULL);
  if(err!=0)
    error(err,"pthread_join");
  }

  printf("global: %ld, even:%ld\n",global);

  return(EXIT_SUCCESS);
}
