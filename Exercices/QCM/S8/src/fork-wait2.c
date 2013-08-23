/**************************************
 * fork-wait.c
 *
 * Programme d'exemple d'utilisation de
 * wait
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>

int main (int argc, char *argv[])  {

  pid_t pid;

  for(int i=0;i<2;i++) {
    pid=fork();
    if (pid==-1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (pid==0) {
      sleep(8);
      return(42);
    }
  }

  int fils;
  int done=false;
  while(!done) {
    int status;
    fils=waitpid(0,&status,0);
    if( (fils==-1) && (errno==ECHILD) )
      done=true;
  }
}
