/**************************************
 * structargs.c
 *
 * exemple de structures comme arguments
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/* Return t2-t1 in microseconds */
long timeval_diff(struct timeval *t2, struct timeval *t1)
{
  long diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
  return (diff);
}

///AAA

#define MILLION 1000000

struct large_t {
  int i;
  char str[MILLION];
};

int sum(struct large_t s1, struct large_t s2) {
  return (s1.i+s2.i);
}

int sumptr(struct large_t *s1, struct large_t *s2) {
  return (s1->i+s2->i);
}

int main(int argc, char *argv[]) {
  struct timeval tvStart, tvEnd;
  int err;
  int n;
  struct large_t one={1,"one"};
  struct large_t two={1,"two"};

  n=sum(one,two);
  n=sumptr(&one,&two);

///BBB

  err=gettimeofday(&tvStart, NULL);
  if(err!=0)
    exit(EXIT_FAILURE);

  err=sum(one,two);

  err=gettimeofday(&tvEnd, NULL);
  if(err!=0)
    exit(EXIT_FAILURE);
  printf("Durée de sum : %ld microsecondes\n",timeval_diff(&tvEnd, &tvStart));

  err=gettimeofday(&tvStart, NULL);
  if(err!=0)
    exit(EXIT_FAILURE);

  err=sumptr(&one,&two);

  err=gettimeofday(&tvEnd, NULL);
  if(err!=0)
    exit(EXIT_FAILURE);

  printf("Durée de sumptr : %ld microsecondes\n",timeval_diff(&tvEnd, &tvStart));
}

