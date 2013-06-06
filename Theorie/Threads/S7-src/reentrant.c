/**************************************
 * reentrant.c
 *
 * Programme d'exemple de fonctions reentrantes
 *
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


///AAA
#include <stdint.h>
#define SIZE 10000

int g_max=INT32_MIN;
int v[SIZE];

int max_vector(int n, int *v) {
  int max=INT32_MIN;
  for(int i=0;i<n;i++) {
    if(v[i]>max)
      max=v[i];
  }
  return max;
}

int max_global(int *v) {
    if (*v>g_max) {
      g_max=*v;
    }
    return(g_max);
}

int max_static(int *v){
  static int s_max=INT32_MIN;
  if (*v>s_max) {
    s_max=*v;
  }
  return(s_max);
}

///BBB

int main (int argc, char *argv[])  {
  srand((int) getpid());
  for (int i=0;i<SIZE;i++) {
    v[i]=rand()%1000000;
  }
  printf("max_vector: %d\n",max_vector(SIZE,v));
  int max_g;
  int max_s;
  for(int i=0;i<SIZE;i++) {
    max_g=max_global(&v[i]);
    max_s=max_static(&v[i]);
  }
  printf("max_global: %d\n",max_g);
  printf("max_static: %d\n",max_s);

  return(EXIT_SUCCESS);
}
