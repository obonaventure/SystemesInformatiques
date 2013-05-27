/**************************************
 * fork-pthread.c
 *
 * Programme d'exemple pour voir le contenu de /proc
 *
 *************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define DELAY 600

pid_t gettid() {
    pid_t tid;
    tid = syscall(SYS_gettid);
    return tid;
}


void *func(void * param) {
  int slept=DELAY;
  printf("thread : %d\n",gettid());
  fflush(stdout);
  while((slept=sleep(slept))!=0) ;
  pthread_exit(NULL);
}

int main (int argc, char *argv[])  {
  int err;
  pid_t pid;
  int status;
  pthread_t thread;
  int slept=DELAY;
  printf("père : %d\n",getpid());
  fflush(stdout);
  pid=fork();
  if (pid==-1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (pid==0) {
    // fils
    printf("fils : %d\n",getpid());
    fflush(stdout);
    while((slept=sleep(slept))!=0) ;
    return(EXIT_SUCCESS);
  }
  else {
    // père
    err=pthread_create(&(thread),NULL,&func,NULL);
    if(err!=0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
    err=pthread_join(thread,NULL);
    if(err!=0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
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
  return(EXIT_SUCCESS);
}

