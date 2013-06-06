/**************************************
 * execbomb.c
 *
 * Programme qui ne se termine jamais
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main (int argc, char *argv[])  {

  int n=2;
  int i=0;
  for(i=0;i<n;i++) {
    sleep(1);
    printf("%d\n",i);
    int err=execve(argv[0], argv, environ);
    if(err!=0) {
      perror("execve");
      exit(EXIT_FAILURE);
    }
  }
  return(EXIT_SUCCESS);
}

