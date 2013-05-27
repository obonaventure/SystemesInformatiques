/**************************************
 * getpid.c
 *
 * Programme d'exemple pour getpid
 *
 **************************************/
///AAA
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  unsigned int sec=30;
  int pid=(int) getpid();

  printf("Processus : %d\n",pid);
  printf("[pid=%d] Sleep : %d secondes\n",pid, sec);
  sec=sleep(sec);
  if(sec==0) {
    printf("[pid=%d] Fin du processus\n",pid );
    return(EXIT_SUCCESS);
  }
  else {
    printf("[pid=%d] Interrompu alors qu'il restait %d secondes\n",pid,sec);
    return(EXIT_FAILURE);
  }
}
