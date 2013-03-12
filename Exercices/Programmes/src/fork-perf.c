/**************************************
 * fork-perf.c
 * 
 * Programme d'exemple pour calculer le coût 
 * de fork
 *
 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 100000

int main (int argc, char *argv[])  {
  int status;
  pid_t pid;

  for(int i=0;i<N;i++) {
    pid=fork();
    if (pid==-1) {
      // erreur à l'exécution de fork
      perror("fork");
      exit(EXIT_FAILURE);
    }
    // pas d'erreur
    if (pid==0) {
      return(EXIT_SUCCESS);
    }
    else {
      int fils=waitpid(pid,&status,0);
      if(fils==-1) {
	perror("wait");
	exit(EXIT_FAILURE);
      }
      if(!WIFEXITED(status)) {
	fprintf(stderr,"Erreur de waitpid\n");
	exit(EXIT_FAILURE);
      }
    }
  }
  return(EXIT_SUCCESS);
    
}

