/**************************************
 * gdbex.c
 *
 * Programme d'exemple pour gdb
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>


int g=0;
int h=0;

int main(int argc, char *argv[]) {

  g=3;
  h=g+h;

  return(EXIT_SUCCESS);
}
