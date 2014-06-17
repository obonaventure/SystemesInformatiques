/***********************************************
 * structptr.c
 *
 * Programme d'exemple de pointeurs vers des
 * structures
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

  struct fraction {
    int num;
    int den;
  };

///AAA
struct fraction demi, quart;
struct fraction *demi_ptr;
struct fraction *quart_ptr;

demi_ptr = &demi;
quart_ptr = &quart;

(*demi_ptr).num = 1;
(*demi_ptr).den = 2;

quart_ptr->num = 1;
quart_ptr->den = 4;
///BBB

  return EXIT_SUCCESS;
}
