/**************************************
 * fork-zombie.c
 *
 * Programme d'exemple d'utilisation de
 * fork qui crée un zombie
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void usage() {
  printf("Usage :\n");
  printf("prog -p num\navec num entier\n");

}

int main (int argc, char *argv[])  {
  pid_t pid;
  char *endptr, *str;
  int err;
  int ch;
  int priority;
  while ((ch = getopt(argc, argv, "p:")) != -1) {
    switch (ch) {
    case 'p':
      priority=(int) strtol(optarg, &endptr, 10);
      if( (priority < 0) || (priority >20) ) {
	printf("La priorité doit être comprise entre 0 et 20\n");
      }
      return(EXIT_FAILURE);
      break;
    case '?':
    default:
      usage();
      return(EXIT_FAILURE);
    }
  }
  pid=fork();

  if (pid==-1) {
    // erreur à l'exécution de fork
    perror("fork");
    exit(EXIT_FAILURE);
  }
  // pas d'erreur
  if (pid==0) {
    // fils
    printf("pid du zombie: %d\n",getpid());
    return(EXIT_SUCCESS);
  }
  else {
    // processus père
    sleep(50);
    err=wait(NULL);
    if(err!=0) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    printf("Fin du processus père [%d]\n",getpid());
    return(EXIT_SUCCESS);
  }
}
///BBB
