/**************************************
 * exhaust-stack.c
 *
 * Programme qui sature le stack
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

///AAA

#define ARRAY_SIZE 10000

int sumn(int i) {
  int array[ARRAY_SIZE];
  printf("Computing sumn(%d)\n",i);
  for(int j=0;j<ARRAY_SIZE;j++){
    array[j]=i;
  }
  if(i>0)
    return (i+sumn(i-1));
  else
    return i;
}

///BBB
int main(int argc, char *argv[]) {
  int n;
  if(argc==2) {
    n=atoi(argv[1]);
  }
  else
    n=5;
  struct rlimit r;

  int err=getrlimit(RLIMIT_STACK,&r);
  if(err!=0) {
    printf("Error\n");
    return(EXIT_FAILURE);
  }
  printf("Softlimit %ld, hard limit %ld\n",(rlim_t) r.rlim_cur,(rlim_t)r.rlim_max);
  printf("La somme des %d premiers entiers est : %d\n",n,sumn(n));

  return(EXIT_SUCCESS);
}
