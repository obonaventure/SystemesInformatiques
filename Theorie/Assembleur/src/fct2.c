/**************************************
 * fct2.c
 *
 * Programme d'exemple pour une fonction
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA
int g=0;
int h=2;

int init() {
  return 1252;
}

int sum(int a, int b) {
  return a+b;
}

int main(int argc, char *argv[]) {
  g=init();
  h=sum(1,2);
  return(EXIT_SUCCESS);
}
