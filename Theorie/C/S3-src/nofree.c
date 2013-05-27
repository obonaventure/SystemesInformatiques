/**************************************
 * nofree.c
 *
 * malloc sans free
 *
 **************************************/

#include <stdio.h>
#include <stdlib.h>
///AAA
#define LEN 1024
int main(int argc, char *argv[]) {

  char *str=(char *) malloc(sizeof(char)*LEN);
  for(int i=0;i<LEN-1;i++) {
    *(str+i)='A';
  }
  *(str+LEN)='\0';  // fin de chaîne
  return(EXIT_SUCCESS);
}

