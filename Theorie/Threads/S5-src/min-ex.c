/**************************************
 * min-ex.c
 *
 * Programme d'exemple pour le linker
 *
 **************************************/

#include "min.h"
#include <stdlib.h>

float min(float a, float b) {
  if(a<b)
    return a;
  else
    return b;
}

static int main(int argc, char*argv[]) {

  if(min(3.0,2.0)!=2.0)
    return(EXIT_FAILURE);

}

