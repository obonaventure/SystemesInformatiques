/**************************************
 * sigusr.c
 *
 * Programme d'exemple d'utilisation des
 * signaux SIGUSR
 *
 *************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

volatile sig_atomic_t n_sigusr1=0;
volatile sig_atomic_t n_sigusr2=0;

static void sig_handler(int);

int main (int argc, char *argv[])  {

  if(signal(SIGUSR1,sig_handler)==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }
  if(signal(SIGUSR2,sig_handler)==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  while( (n_sigusr1+n_sigusr2) <5) {
    // vide
  }

  printf("Fin du processus\n");
  printf("Reçu %d SIGUSR1 et %d SIGUSR2\n",n_sigusr1,n_sigusr2);
  return(EXIT_SUCCESS);
}

static void sig_handler(int signum) {

  if(signum==SIGUSR1) {
    n_sigusr1++;
  }
  else {
    if(signum==SIGUSR2) {
      n_sigusr2++;
    }
    else {
      char *msg="Reçu signal inattendu\n";
      write(STDERR_FILENO,msg,strlen(msg));
      _exit(EXIT_FAILURE);
    }
  }
}

///BBB
