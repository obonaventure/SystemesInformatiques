/**************************************
 * strerror.c
 *
 * Programme d'exemple strerror
 *
 **************************************/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])  {

  for(int i=0; i<999;i++) {
    printf("strerror[%d] est à l'adresse %p\n",i,strerror(i));
  };

  return(EXIT_SUCCESS);
}
