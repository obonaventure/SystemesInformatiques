/**************************************
 * alarm.c
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
#include <stdbool.h>
#include <setjmp.h>

sigjmp_buf env;

static void sig_handler(int);

int main (int argc, char *argv[])  {
  char c;
  printf("Tapez return en moins de 5 secondes !\n");
  fflush(stdout);
  if(signal(SIGALRM,sig_handler)==SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }
  // sigalrm interrompt les appels système
  if(siginterrupt(SIGALRM,true)<0) {
    perror("siginterrupt");
    exit(EXIT_FAILURE);
  }
  int r=0;
  if(sigsetjmp(env,1)==0) {
    // sig_handler n'a pas encore été appelé
    alarm(5);
    r=read(STDIN_FILENO,&c,1);
  }
  else {
    // sig_handler a déjà été exécuté
    // le délai a déjà expiré, inutile de faire read
  }
  alarm(0); // arrêt du timer
  if((r==1)&&(c=='\n')) {
    printf("Gagné\n");
    exit(EXIT_SUCCESS);
  }
  else {
    printf("Perdu !\n");
    exit(EXIT_FAILURE);
  }
}

static void sig_handler(int signum) {
  siglongjmp(env,1);
}

///BBB
