/**************************************
 * cmdline.c
 *
 * Programme affichant ses arguments
 * sur la sortie standard
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
  int i;
  printf("Ce programme a %d argument(s)\n",argc);
  for( i=0; i < argc; i++ ) {
    printf("argument[%d] : %s\n",i, argv[i] );
  }
  return(EXIT_SUCCESS);
}
