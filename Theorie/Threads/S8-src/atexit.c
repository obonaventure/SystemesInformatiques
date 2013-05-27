/**************************************
 * atexit.c
 *
 * Programme d'exemple d'utilisation de
 * atexit
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>

void e1() {
  printf("Exécution de la fonction e1\n");
}

int main (int argc, char *argv[])  {

  int err;
  err=atexit(e1);
  if(err==-1) {
    perror("atexit");
    exit(EXIT_FAILURE);
  }
  return(EXIT_SUCCESS);

}
///BBB
