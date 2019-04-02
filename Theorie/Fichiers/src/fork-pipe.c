/**************************************
 * fork-pipe.c
 *
 * Programme d'exemple d'utilisation de
 * pipe en combinaison avec fork
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

void exit_on_error(char *s) {
  perror(s);
  exit(EXIT_FAILURE);
}


int main (int argc, char *argv[])  {
  int status;
  pid_t pid;
  int fd[2];
  int err;

  if ( pipe(fd)==-1)
    exit_on_error("pipe");

  pid=fork();

  if (pid==-1) {
    // erreur à l'exécution de fork
    exit_on_error("fork");
  }
  // pas d'erreur
  if (pid==0) {
    int count=0;
    int finished=false;
    int n;
    // processus fils, lecture du pipe
    if(close(fd[1])==-1)
      exit_on_error("close");
    while ( !finished) {
      err=read(fd[0],(void *) &n,sizeof(int));
      if(err==sizeof(int))
	// entier reçu
	count++;
      else
	if(err==0)
	  // fin de fichier
	  finished=true;
	else
	  exit_on_error("read");
    }
    if(close(fd[0])==-1)
      exit_on_error("close");
    printf("Reçu : %d entiers\n",count);
    return(EXIT_SUCCESS);
  }
  else {
    // processus père
    if(close(fd[0])==-1)
      exit_on_error("close");
    for(int i=0;i<100000;i++) {
      if(write(fd[1],(void *) &i,sizeof(int))==-1)
	exit_on_error("write");
    }
    if( close(fd[1])==-1)
      exit_on_error("close(fd[1])");

    int fils=waitpid(pid,&status,0);
    if(fils==-1) {
      exit_on_error("wait");
    }
    // fils terminé correctement
  }
}
///BBB
