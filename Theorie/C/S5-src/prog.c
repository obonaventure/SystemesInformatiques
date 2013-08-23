/**************************************
 * prog
 *
 * Programme d'exemple pour le linker
 *
 **************************************/

#include <stdlib.h>
#include <stdio.h>
///AAA
#include "min.h"
#include "module.h"

#define SIZE 4

extern int num1; // définie dans un autre module
int num2=1252;   // accessible depuis un autre module
static int num3=-1; // accessible uniquement dans ce module

void f() {
  static int n=0;
  int loc=2;
  if(n==0)
    printf("n est à  l'adresse %p et loc à l'adresse %p\n",&n,&loc);
  printf("f, n=%d\n",n);
  n++;
}

int main(int argc, char* argv[]) {

  float v[SIZE]={1.0, 3.4, -2.4, 9.9};
  printf("Minimum: %f\n",vmin(SIZE,v));
  f();
  f();
  printf("Minimum(0.0,1.1)=%f\n",min(0.0,1.1));
  return(EXIT_SUCCESS);
}


