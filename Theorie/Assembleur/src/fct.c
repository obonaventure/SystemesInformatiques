/**************************************
 * fct.c
 *
 * Programme d'exemple pour une fonction
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

///AAA
int g=0;
int h=2;
void init(int i, int j) {
 g=i;
 h=j;
}

int main(int argc, char *argv[]) {
  init(1252,1);
  return(EXIT_SUCCESS);
}
