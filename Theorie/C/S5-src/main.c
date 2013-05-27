/**************************************
 * main.c
 *
 * Programme d'exemple pour le linker
 *
 **************************************/

#include "min.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  float f1=3.45;
  float f2=-4.12;
  printf("Minimum(%f,%f)=%f\n",f1,f2,min(f1,f2));
  return(EXIT_SUCCESS);
}

