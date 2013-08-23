/**************************************
 * process-sem-before.c
 *
 * Programme d'exemple de sémaphores nommés
 * La fonction after ne peut s'exécuter
 * qu'après la fonction before
 **************************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <unistd.h>

void error(int err, char *msg) {
  fprintf(stderr,"%s a retourné %d, message d'erreur : %s\n",msg,err,strerror(errno));
  exit(EXIT_FAILURE);
}


///AAA

sem_t *semaphore;

void after() {
  sem_wait(semaphore);
  // do something
  for(int j=0;j<1000000;j++) {
  }
  printf("after done, pid=%d\n",(int) getpid());
}

int main (int argc, char *argv[])  {
  int err;

  // semaphore a été créé par before
  semaphore=sem_open("lsinf1252",0);
  if(semaphore==SEM_FAILED) {
      error(-1,"sem_open");
  }
  after();

  err=sem_close(semaphore);
  if(err!=0) {
      error(err,"sem_close");
  }
  err=sem_unlink("lsinf1252");
  if(err!=0) {
      error(err,"sem_unlink");
  }
  return(EXIT_SUCCESS);
}
///BBB
