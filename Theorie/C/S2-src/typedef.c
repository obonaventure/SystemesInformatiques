/***********************************************
 * typedef.c
 *
 * Programme d'exemple d'utilisation de typedef
 *
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>

///EEE
typedef unsigned int u_int_t;
typedef unsigned long u_long_t;
///FFF

///CCC
typedef int * int_ptr;
typedef char * string;
///DDD

///AAA
// structure pour stocker une fraction
typedef struct fraction {
  double numerator;
  double denominator;
} Fraction ;

typedef int Entier;

int main(int argc, char *argv[])
{
  Fraction demi = {1, 2};
  Entier i = 2;
  // ...
  return EXIT_SUCCESS;
}
///BBB
