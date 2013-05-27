/**************************************
 * proc.c
 *
 * Programme d'exemple pour les procédures
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA
int g=0;
int h=2;

void increase() {
 g=g+h;
}

void init_g() {
 g=1252;
}

int main(int argc, char *argv[]) {
  init_g();
  increase();
  return(EXIT_SUCCESS);
}
