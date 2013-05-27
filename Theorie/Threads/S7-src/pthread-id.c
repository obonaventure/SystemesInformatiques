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

#define MAXNUM 1000
#define NTHREADS 4

struct result {
  long x;
  long y;
  long z;
};

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}


long power(long i, long j) {
  long r=i;
  while(j>0) {
    r=r*i;
    j--;
  }
  return r;
}

void g();

void *f1( void* param) {

  printf("f1 a calculé %d"
  return(NULL);
}


void *fermat (void * param) {

  struct result *r=(struct result *)malloc(sizeof(struct result));
  if(r==NULL)
    error(-1,"malloc");

  long n=(long) param;
  for(long x=1;x<MAXNUM;x++) {
    for(long y=1;y<MAXNUM;y++) {
      for(int z=1;z<MAXNUM;z++) {
	if( (power(x,n)+power(y,n))==power(z,n) ) {
	      r->x=x;
	      r->y=y;
	      r->z=z;
	      return((void *) r);
	}
      }
    }
  }
  return(NULL);
}

int main (int argc, char *argv[])  {
  pthread_t threads[NTHREADS];
  int err;

  err=pthread_create(&(threads[i]),NULL,&fermat,(void *)(long) i+2);
  if(err!=0)
    error(err,"pthread_create");




  for(int i=0;i<NTHREADS;i++) {
    void *p;
    err=pthread_join(threads[i],(void **)&(p));

    if(err!=0)
      error(err,"pthread_create");
    //if(p!=NULL) {
    //struct result r;
      //      r=(struct result) p;
      //printf("Trouvé pour %d : x=%ld, y=%ld, z=%ld\n",i+2,r[i].x,r[i].y, r[i].z);
  }


  return(EXIT_SUCCESS);
}
