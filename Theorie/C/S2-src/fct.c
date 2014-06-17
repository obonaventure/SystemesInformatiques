/***********************************************
 * fct.c
 *
 * Programme d'exemple d'utilisation de fonctions
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///AAA

void usage()
{
  printf("Usage : ...\n");
}

///BBB

///CCC

int twotimes(int n)
{
  return 2 * n;
}

int two_times(int n)
{
  n = 2 * n;
  return n;
}

///DDD


///EEE

int times_two(int *n)
{
  return (*n) + (*n);
}

int timestwo(int *n)
{
  *n = (*n) + (*n);
  return *n;
}

void f()
{
  int i = 1252;
  printf("i:%d\n", i);
  printf("times_two(&i)=%d\n", times_two(&i));
  printf("après times_two, i:%d\n", i);
  printf("timestwo(&i)=%d\n", timestwo(&i));
  printf("après timestwo, i:%d\n", i);
}

///FFF

void plusun(int size, int *v) {
  int i;
  for(i=0;i<size;i++)
    v[i]++;
}

///GGG


int main(int argc, char *argv[]) {

  int i=1252;
  int j;

  f();

   return(EXIT_SUCCESS);
}
