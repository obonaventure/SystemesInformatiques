/**************************************
 * typecast.c
 *
 * Programme d'exemple de conversion entre
 * types de données
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  ///AAA
  int i=1;
  float f=1e20;
  double d=1e100;

  printf("i [int]: %d, [float]:%f, [double]:%f\n",i,(float)i,(double)i);
  printf("f [int]: %d, [float]:%f, [double]:%f\n",(int)f,f,(double)f);
  printf("d [int]: %d, [float]:%f, [double]:%f\n",(int)d,(float)d,d);
  printf("sizeof -> int:%d float:%d double:%d\n",(int)sizeof(int), (int)sizeof(float), (int)sizeof(double));

  ///BBB
   return(EXIT_SUCCESS);
}
