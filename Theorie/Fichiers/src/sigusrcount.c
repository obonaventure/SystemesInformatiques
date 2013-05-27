/**************************************
 * sigusrcount.c
 *
 * Programme d'exemple d'utilisation des
 * signaux SIGUSR
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t n_sigusr1=0;

static void sig_handler(int);

int main (int argc, char *argv[])  {

  if(signal(SIGUSR1,sig_handler)==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }
  int duree=60;
  while(duree>0) {
    printf("Exécution de sleep(%d)\n",duree);
    duree=sleep(duree);
  }
  printf("Fin du processus\n");
  printf("Reçu %d SIGUSR1\n",n_sigusr1);
  return(EXIT_SUCCESS);
}

static void sig_handler(int signum) {

  if(signum==SIGUSR1) {
    n_sigusr1++;
  }
}

///BBB
