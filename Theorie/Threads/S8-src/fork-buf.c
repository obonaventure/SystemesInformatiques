/**************************************
 * fork.c
 *
 * Programme d'exemple d'utilisation de
 * fork
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>


void output(char c) {
  printf("Processus : %d\n",getpid());
  srand(getpid()+time(NULL));
  for(int i=0;i<60;i++) {
    putchar(c);
    int err=usleep((unsigned int) (rand()%10000));
    if(err<0) {
      perror("usleep");
      exit(EXIT_FAILURE);
    }
  }
}

int main (int argc, char *argv[])  {

  if(argc > 1) {
    setbuf(stdout,NULL);
  }

  pid_t pid;

  pid=fork();
  if (pid==-1) {
    // erreur à l'exécution de fork
    perror("fork");
    exit(EXIT_FAILURE);
  }
  // pas d'erreur
  if (pid==0) {
    // processus fils
    output('f');
    return(EXIT_SUCCESS);
  }
  else {
    // processus père
    output('P');
    printf("\n");
    sleep(1);
    // ...
    return(EXIT_SUCCESS);
  }
}
///BBB
