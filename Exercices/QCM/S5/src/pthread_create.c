#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void error(int err, char *msg) {
  fprintf(stderr,"%s a retourne %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}
// correct
void *f(void * param) {
  // incomplet
  return NULL;
}

// incorrect
void *f1(void * param) {
  // incomplet
  return NULL;
}
// incorrect
void *f2(void param) {
  // incomplet
  return NULL;
}
// incorrect
void f3(void * param) {
  // incomplet
  return NULL;
}
// incorrect
void *f4(void ** param) {
  // incomplet
  return NULL;
}


int main (int argc, char *argv[])  {

  pthread_t t;
  int err;
  char *s;
  char s1;
  // correct
  err=pthread_create(&t,NULL,&(f),(void *) s);
  // incorrect
  err=pthread_create(&t,NULL,&(f1),(void *) &(s));
  err=pthread_create(t,NULL,f2,s);
  err=pthread_create(*t,NULL,*f3,(void *) *s);
  err=pthread_create(&t,NULL,&(f),s1);
  if(err!=0)
    error(err,"pthread_create");

  err=pthread_join(t,(void **) &r);
  if(err!=0)
    error(err,"pthread_join");

  printf("%f \n",(float) (*r));

  return(EXIT_SUCCESS);
}
