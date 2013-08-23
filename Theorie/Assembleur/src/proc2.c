/**************************************
 * proc2.c
 *
 * Programme d'exemple pour les procédures
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA
int g=0;
int h=2;

void q() {
 g=1252;
}

void p() {
  q();
  g=g+h;
}



int main(int argc, char *argv[]) {
  p();
  return(EXIT_SUCCESS);
}
