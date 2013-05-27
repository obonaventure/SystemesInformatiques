/***********************************************
 * perf.c
 *
 * Mesure de temps de calcul via gettimeofday
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Return t2-t1 in microseconds */
long timeval_diff(struct timeval *t2, struct timeval *t1)
{
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
  return (diff);
}
// n : number of iterations of the loop
void compute(int n) {
  // long computation
  double sum=0;
  int i;
  for(i=0;i<n;i++) {
    sum=sum+i;
  }
}

int main(int argc, char *argv[])
{
  struct timeval tvStart, tvEnd;
  int err;
  int num; // number of operations for compute
  if(argc!=2)
    exit(EXIT_FAILURE);
  else
    num=atoi(argv[1]);

  err=gettimeofday(&tvStart, NULL);
  if(err!=0)
    exit(EXIT_FAILURE);

  // long computation
  compute(num);

  err=gettimeofday(&tvEnd, NULL);
  if(err!=0)
    exit(EXIT_FAILURE);

  printf("Duration : %ld microseconds\n", timeval_diff(&tvEnd, &tvStart));

  return(EXIT_SUCCESS);
}

