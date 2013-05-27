/**************************************
 * pthread-mutex.c
 *
 * Programme d'exemple de pthread avec
 * utilisation de mutex pour éviter une
 * violation de section critique
 *
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

/* Return t2-t1 in microseconds */
long timeval_diff(struct timeval *t2, struct timeval *t1)
{
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
  return (diff);
}

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}

///AAA
#include <pthread.h>
#define LOOP 40000
#define LOOP_CRITIQUE 40000
#define N 4

int percent; // pourcentage de temps en section critique
int nthreads; // nombre de threads
pthread_mutex_t mutex;

void critique() {
  long j=0;
  for(int i=0;i<(LOOP_CRITIQUE*percent)/100;i++) {
    j+=i;
    // ...
  }
}

void noncritique() {
  int j=0;
  for(int i=0;i<(LOOP_CRITIQUE*(100-percent))/100;i++) {
    j-=i;
    // ...
  }
}


void *func(void * param) {
  for(int j=0;j<LOOP/nthreads;j++) {
    pthread_mutex_lock(&mutex);
    critique();
    pthread_mutex_unlock(&mutex);
    noncritique();
  }
  return(NULL);
}

int main (int argc, char *argv[])  {
  int err;
  struct timeval tvStart, tvEnd;
  long mesures[N];

  if(argc!=3)
    return(EXIT_FAILURE);

  char *endptr;
  percent=strtol(argv[1],&endptr,10);
  nthreads=strtol(argv[2],&endptr,10);

  pthread_t thread[nthreads];

  err=pthread_mutex_init( &mutex, NULL);
  if(err!=0)
      error(err,"pthread_mutex_init");

  for (int j=0;j<N;j++)  {

    err=gettimeofday(&tvStart, NULL);
    if(err!=0)
      exit(EXIT_FAILURE);

    for(int i=0;i<nthreads;i++) {
      err=pthread_create(&(thread[i]),NULL,&func,NULL);
      if(err!=0)
	error(err,"pthread_create");
    }

    for(int i=nthreads-1;i>=0;i--) {
      err=pthread_join(thread[i],NULL);
      if(err!=0)
	error(err,"pthread_join");
    }
    err=gettimeofday(&tvEnd, NULL);
    if(err!=0)
      exit(EXIT_FAILURE);

    mesures[i]=timeval_diff(&tvEnd, &tvStart);
    sum+=mesures[i];

  }
  printf("%d, %d, %ld\n",nthreads,percent,sum/N);

  err=pthread_mutex_destroy(&mutex);
  if(err!=0)
    error(err,"pthread_destroy");

  return(EXIT_SUCCESS);
}
