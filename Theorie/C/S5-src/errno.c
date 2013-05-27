/**************************************
 * errno.c
 *
 * Programme d'exemple pour errno
 *
 **************************************/
///AAA
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if(setenv(NULL,NULL,1)!=0) {
    fprintf(stderr,"Erreur : errno=%d %s\n",errno,strerror(errno));
  }
  if(setenv("PATH=","/usr/bin",1)!=0) {
    fprintf(stderr,"Erreur : errno=%d %s\n",errno,strerror(errno));
   }


}

