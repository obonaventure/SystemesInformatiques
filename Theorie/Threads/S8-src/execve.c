/**************************************
 * execve.c
 *
 * Programme d'exemple pour execve
 *
 *************************************/

///AAA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])  {

  char *arguments[]={"expr", "1", "+", "2", NULL};
  char *environnement[]={"LANG=fr",NULL};

  printf("Exécution du processus %d\n",getpid());
  printf("Exécution de /usr/bin/expr\n");
  int err=execve("/usr/bin/expr", arguments, environnement);
  if(err!=0) {
    perror("execve");
    exit(EXIT_FAILURE);
  }
  // jamais atteint
  printf("Ce message ne sera jamais affiché\n");
  return(EXIT_SUCCESS);

}

