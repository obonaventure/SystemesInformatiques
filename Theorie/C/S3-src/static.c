/**************************************
 * static.c
 *
 * Programme d'exemple d'utilisation de static
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>


void f(int i) {
  static int sum;

}

int main(int argc, char *argv[]) {

  f(1);

  f(2);

  return(EXIT_SUCCESS);
}
