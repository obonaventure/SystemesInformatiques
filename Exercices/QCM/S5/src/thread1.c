#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Array {
  int length;
  int *tab;
};

typedef struct Array Array_t;


void error(int err, char *msg) {
  fprintf(stderr,"%s a retourne %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}


void *thread_min(void * param) {
  Array_t *a=(Array_t *) param;
  int *r=(int *)malloc(sizeof(int));
  *r=a->tab[0];
  for(int i=1;i<a->length;i++) {
    if(a->tab[i]<*r)
      *r=a->tab[i];
  }

  return((void *) r);
}

void *thread_max(void * param) {
  Array_t *a=(Array_t *) param;
  int *r=(int *)malloc(sizeof(int));
  *r=a->tab[0];
  for(int i=1;i<a->length;i++) {
    if(a->tab[i]>*r)
      *r=a->tab[i];
  }

  return((void *) r);
}

int main (int argc, char *argv[])  {

  int tab[]={12, 4, 3, 7, 8 , 9 , 10};
  Array_t array = {.length=7, .tab=tab};
  pthread_t first;
  pthread_t second;
  int *r_min;
  int *r_max;

  int err;
  int min;
  int max;
  err=pthread_create(&first,NULL,&thread_min,&(array));
  if(err!=0)
    error(err,"pthread_create");

  err=pthread_join(first,(void **) &r_min);
  if(err!=0)
    error(err,"pthread_join");

  printf("min:%ld \n",(long) (*r_min));

  return(EXIT_SUCCESS);
}
